"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

# Unit tests for angle-mode shadow-curvature publishing (bp_kappa_cmd).
#
# The shadow value is consumed by carcontroller as the input to ford.h's angle-mode
# deviation check (Lane_Assist_Data1 bytes 5-6, judged against angle_meas). These tests
# pin the truthfulness contract: whenever the planner kappa cannot honestly describe the
# car's steering -- inactive, human-turn override, stall blip, driver pressing -- the
# published shadow must equal the measured curvature, so the panda-latched value always
# stays inside the check's band and re-engage frames never compare a stale zero against
# real measured curvature.

import math
import unittest
from dataclasses import dataclass
from types import SimpleNamespace
from unittest import mock

from opendbc.car import structs
from opendbc.car.ford.values import CAR, CarControllerParams
from opendbc.car.interfaces import scale_tire_stiffness
from opendbc.sunnypilot.car.ford import fordcan_ext, lateral_curv_ext
from opendbc.sunnypilot.car.ford.values_ext import (
  FORD_DBC_PATH_ANGLE_MAX,
  FORD_DBC_PATH_ANGLE_MIN,
  FORD_INTERNAL_PATH_ANGLE_MAX,
  FORD_INTERNAL_PATH_ANGLE_MIN,
  FordSafetyFlagsSP,
  clip_ford_path_angle_internal,
  clip_ford_path_angle_wire,
)
from opendbc.sunnypilot.car.ford.lateral_curv_ext import LateralCurvExt
from opendbc.sunnypilot.car.ford.lateral_angle_ext import LateralAngleExt


def _explorer_cp():
  CP = structs.CarParams()
  CP.mass = 2050.
  CP.wheelbase = 3.025
  CP.steerRatio = 16.8
  CP.centerToFront = CP.wheelbase * 0.44
  CP.tireStiffnessFactor = 0.82
  CP.tireStiffnessFront, CP.tireStiffnessRear = scale_tire_stiffness(
    CP.mass, CP.wheelbase, CP.centerToFront, CP.tireStiffnessFactor)
  return CP


class _FakeLiveDelay:
  lateralDelay = 0.2


class _FakeSubMaster:
  def __init__(self, *args, **kwargs):
    self.updated = {s: False for s in ('modelV2', 'liveParameters', 'selfdriveState', 'radarState', 'liveDelay')}

  def update(self, timeout=0):
    pass

  def __getitem__(self, key):
    if key == 'liveDelay':
      return _FakeLiveDelay()
    raise KeyError(key)


class _ForcedDetector:
  def __init__(self, active):
    self.active = active

  def update(self, *_args):
    return self.active

  def reset(self):
    pass


class _GatedDetector:
  def __init__(self):
    self.enabled = None

  def update(self, enabled, *_args):
    self.enabled = enabled
    return bool(enabled)

  def reset(self):
    pass


class _FakeParams:
  def __init__(self, values):
    self.values = values

  def get(self, key, return_default=False):
    return self.values.get(key)


class _CapturePacker:
  def __init__(self):
    self.calls = []

  def make_can_msg(self, name, bus, values):
    self.calls.append((name, bus, values.copy()))
    return 0, bytes(8), bus


@dataclass
class _CSOut:
  vEgoRaw: float = 15.0
  vEgo: float = 15.0
  steeringPressed: bool = False
  steeringAngleDeg: float = 0.0
  yawRate: float = 0.0


class _CS:
  def __init__(self, **kwargs):
    self.out = _CSOut(**kwargs)
    self.lat_ctl_lim_stat = 0


@dataclass
class _CC:
  latActive: bool = True


@dataclass
class _Actuators:
  curvature: float = 0.0


class _Harness(LateralCurvExt, LateralAngleExt):
  """Mirrors CarController's mixin composition (see carcontroller.py)."""

  def __init__(self, CP, CP_SP=None):
    self.CP = CP  # CarControllerBase initializes this before the lateral mixins.
    with mock.patch.object(lateral_curv_ext.messaging, 'SubMaster', _FakeSubMaster):
      LateralCurvExt.__init__(self, CP, CP_SP)
    LateralAngleExt.__init__(self, CP, CP_SP)


def _pinion_harness(flag):
  """Harness with the STEER_ANGLE_CURVATURE flag set (or not) on CP_SP, detector stubbed."""
  CP = _explorer_cp()
  CP_SP = structs.CarParamsSP()
  if flag:
    CP_SP.safetyParam |= FordSafetyFlagsSP.STEER_ANGLE_CURVATURE
  ext = _Harness(CP, CP_SP)
  ext.human_turn_detector = _ForcedDetector(False)
  return ext, CP


class TestShadowCurvaturePublishing(unittest.TestCase):
  V_EGO = 15.0
  YAW_RATE = 0.75  # rad/s -> measured curvature = -0.75 / 15 = -0.05 (OP convention)

  def setUp(self):
    self.CP = _explorer_cp()
    self.ext = _Harness(self.CP)
    self.ext.human_turn_detector = _ForcedDetector(False)
    self.cs = _CS(vEgoRaw=self.V_EGO, vEgo=self.V_EGO, yawRate=self.YAW_RATE)
    self.measured = -self.YAW_RATE / self.V_EGO

  def _update(self, lat_active=True):
    return self.ext.update_angle_strategy(_CC(latActive=lat_active), self.cs, _Actuators(curvature=0.01), self.CP)

  def test_inactive_publishes_measured(self):
    result = self._update(lat_active=False)
    self.assertEqual(result.path_angle, 0.0)
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, self.measured)

  def test_human_turn_override_publishes_measured(self):
    self.ext.human_turn_detector = _ForcedDetector(True)
    result = self._update()
    self.assertTrue(self.ext.angle_human_turn_active)
    self.assertEqual(result.path_angle, 0.0)
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, self.measured)

  def test_human_turn_toggle_controls_angle_mode(self):
    detector = _GatedDetector()
    self.ext.human_turn_detector = detector
    self.ext.enable_human_turn_detection_curv = False
    self._update()
    self.assertFalse(detector.enabled)
    self.assertFalse(self.ext.angle_human_turn_active)

    self.ext.enable_human_turn_detection_curv = True
    self._update()
    self.assertTrue(detector.enabled)
    self.assertTrue(self.ext.angle_human_turn_active)

  def test_human_turn_toggle_disables_proactive_release_blip(self):
    self.ext.enable_human_turn_detection_curv = False
    self.ext.press_timer_s = 1.0
    result = self._update()

    self.assertEqual(self.ext.press_timer_s, 0.0)
    self.assertEqual(self.ext.stall_blip_frames_left, 0)
    self.assertFalse(self.ext.angle_stall_blip_active)
    self.assertNotEqual(result.path_angle, 0.0)

  def test_human_turn_toggle_enables_proactive_release_blip(self):
    self.ext.enable_human_turn_detection_curv = True
    self.ext.press_timer_s = 1.0
    result = self._update()

    self.assertEqual(self.ext.press_timer_s, 0.0)
    self.assertEqual(self.ext.stall_blip_frames_left, 5)
    self.assertTrue(self.ext.angle_stall_blip_active)
    self.assertEqual(result.path_angle, 0.0)

  def test_stall_blip_publishes_measured(self):
    self.ext.stall_blip_frames_left = 3
    result = self._update()
    self.assertTrue(self.ext.angle_stall_blip_active)
    self.assertEqual(result.path_angle, 0.0)
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, self.measured)

  def test_pressed_publishes_measured(self):
    self.cs.out.steeringPressed = True
    self._update()
    self.assertFalse(self.ext.angle_human_turn_active)
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, self.measured)

  def test_hands_off_publishes_clipped_planner_kappa(self):
    # planner wants +0.01 while measured is -0.05: the deviation clip (active above 9 m/s)
    # bounds the shadow to measured + CURVATURE_ERROR, not measured itself -- hands-off
    # behavior is unchanged by the truthful-shadow sites.
    self._update()
    expected = self.measured + CarControllerParams.CURVATURE_ERROR
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, expected)
    self.assertNotAlmostEqual(self.ext.bp_kappa_cmd, self.measured)
    self.assertTrue(self.ext.bp_curvature_deviation_limited)


class TestLaneChangeReversalUnwind(unittest.TestCase):
  V_EGO = 15.0

  def setUp(self):
    self.CP = _explorer_cp()
    self.ext = _Harness(self.CP)
    self.ext.human_turn_detector = _ForcedDetector(False)
    self.ext.path_angle_blend_ratio = 0.0  # isolate planner curvature in these state-machine tests
    self.model = SimpleNamespace(
      orientationRate=SimpleNamespace(z=[0.0] * 33),
      meta=SimpleNamespace(laneChangeState=2, laneChangeDirection=0),
    )
    self.ext.model = self.model

  def _update(self, measured_curvature, desired_curvature, v_ego=None, lat_active=True):
    v = self.V_EGO if v_ego is None else v_ego
    cs = _CS(vEgoRaw=v, vEgo=v, yawRate=-measured_curvature * v)
    return self.ext.update_angle_strategy(
      _CC(latActive=lat_active), cs, _Actuators(curvature=desired_curvature), self.CP)

  def test_positive_to_negative_reversal_unwinds_to_neutral(self):
    self.ext.path_angle_last = 0.09

    first = self._update(0.007, -0.002)
    second = self._update(0.007, -0.002)

    self.assertNotEqual(first.path_angle, 0.0)
    self.assertTrue(self.ext.angle_reversal_unwind_active)
    self.assertGreaterEqual(second.path_angle, 0.0)
    self.assertLess(abs(second.path_angle), abs(first.path_angle))
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, 0.007)

  def test_negative_to_positive_reversal_is_symmetric(self):
    self.ext.path_angle_last = -0.09

    first = self._update(-0.007, 0.002)
    second = self._update(-0.007, 0.002)

    self.assertTrue(self.ext.angle_reversal_unwind_active)
    self.assertLessEqual(second.path_angle, 0.0)
    self.assertLess(abs(second.path_angle), abs(first.path_angle))
    self.assertAlmostEqual(self.ext.bp_kappa_cmd, -0.007)

  def test_recent_lane_change_memory_covers_delayed_countersteer(self):
    self._update(0.007, 0.002)
    self.model.meta.laneChangeState = 0
    self.ext.path_angle_last = 0.09

    self._update(0.007, -0.002)
    self._update(0.007, -0.002)

    self.assertGreater(self.ext.reversal_recent_lane_change_s, 0.0)
    self.assertTrue(self.ext.angle_reversal_unwind_active)

  def test_low_speed_behavior_is_unchanged(self):
    result = self._update(0.007, -0.002, v_ego=8.0)

    self.assertFalse(self.ext.bp_curvature_deviation_limited)
    self.assertFalse(self.ext.angle_reversal_unwind_active)
    self.assertLess(result.path_angle, 0.0)

  def test_no_reversal_unwind_outside_lane_change_window(self):
    self.model.meta.laneChangeState = 0
    self.ext.path_angle_last = 0.09

    for _ in range(3):
      result = self._update(0.007, -0.002)

    self.assertFalse(self.ext.angle_reversal_unwind_active)
    self.assertGreater(result.path_angle, 0.0)

  def test_pre_lane_change_does_not_arm_unwind(self):
    self.model.meta.laneChangeState = 1
    self.ext.path_angle_last = 0.09

    for _ in range(3):
      result = self._update(0.007, -0.002)

    self.assertEqual(self.ext.reversal_recent_lane_change_s, 0.0)
    self.assertFalse(self.ext.angle_reversal_unwind_active)
    self.assertGreater(result.path_angle, 0.0)

  def test_unwind_exits_when_measured_curvature_reaches_zero_band(self):
    self.ext.path_angle_last = 0.09
    self._update(0.007, -0.002)
    self._update(0.007, -0.002)
    self.assertTrue(self.ext.angle_reversal_unwind_active)

    first_exit = self._update(0.001, -0.002)
    result = self._update(0.001, -0.002)

    self.assertFalse(self.ext.angle_reversal_unwind_active)
    self.assertLess(abs(first_exit.path_angle), 0.09)
    self.assertLess(result.path_angle, 0.0)

  def test_inactive_resets_reversal_state(self):
    self.ext.reversal_recent_lane_change_s = 2.0
    self.ext.reversal_confirm_s = 0.1
    self.ext.angle_reversal_unwind_active = True

    result = self._update(0.007, -0.002, lat_active=False)

    self.assertEqual(result.path_angle, 0.0)
    self.assertEqual(self.ext.reversal_recent_lane_change_s, 0.0)
    self.assertEqual(self.ext.reversal_confirm_s, 0.0)
    self.assertFalse(self.ext.angle_reversal_unwind_active)


class TestLowSpeedSharpCurveHold(unittest.TestCase):
  """Low-speed deceleration must not unwind angle mode while the car still under-tracks a sharp request."""

  def setUp(self):
    self.CP = _explorer_cp()
    self.ext = _Harness(self.CP)
    self.ext.human_turn_detector = _ForcedDetector(False)
    self.ext.path_angle_blend_ratio = 0.0

  def _update(self, v_ego, measured_curvature, desired_curvature, *, pressed=False, lat_active=True):
    cs = _CS(vEgoRaw=v_ego, vEgo=v_ego, yawRate=-measured_curvature * v_ego, steeringPressed=pressed)
    return self.ext.update_angle_strategy(
      _CC(latActive=lat_active), cs, _Actuators(curvature=desired_curvature), self.CP)

  def _settle(self, v_ego, measured_curvature, desired_curvature, frames=20):
    result = None
    for _ in range(frames):
      result = self._update(v_ego, measured_curvature, desired_curvature)
    return result

  def test_deceleration_cannot_unwind_undertracked_sharp_curve(self):
    first = self._settle(4.7, 0.047, 0.070)
    raw_second = 0.064 * 4.1 * 1.30
    second = self._update(4.1, 0.040, 0.064)

    self.assertLess(raw_second, abs(first.path_angle))
    self.assertTrue(self.ext.bp_low_speed_curve_hold_active)
    self.assertAlmostEqual(second.path_angle, first.path_angle)

  def test_hold_is_symmetric(self):
    first = self._settle(4.7, -0.047, -0.070)
    second = self._update(4.1, -0.040, -0.064)

    self.assertTrue(self.ext.bp_low_speed_curve_hold_active)
    self.assertAlmostEqual(second.path_angle, first.path_angle)

  def test_hold_addition_is_bounded(self):
    self.ext.path_angle_last = 0.40
    # The existing soft ROC needs a few frames to move down from 0.40; once it catches the
    # bounded hold target, the hold itself must settle exactly 0.10 rad above the raw result.
    result = None
    for _ in range(4):
      result = self._update(3.0, 0.025, 0.040)

    raw = 0.040 * 3.0 * 1.30
    self.assertTrue(self.ext.bp_low_speed_curve_hold_active)
    self.assertAlmostEqual(result.path_angle, raw + 0.10)

  def test_model_exit_releases_hold(self):
    first = self._settle(4.7, 0.047, 0.070)
    held = self._update(4.1, 0.040, 0.064)
    exiting = self._update(4.1, 0.040, 0.030)

    self.assertAlmostEqual(held.path_angle, first.path_angle)
    self.assertFalse(self.ext.bp_low_speed_curve_hold_active)
    self.assertLess(abs(exiting.path_angle), abs(held.path_angle))

  def test_gentle_curve_is_unchanged(self):
    first = self._settle(4.7, 0.006, 0.012)
    second = self._update(4.1, 0.005, 0.010)

    self.assertFalse(self.ext.bp_low_speed_curve_hold_active)
    self.assertLess(abs(second.path_angle), abs(first.path_angle))

  def test_driver_press_releases_hold(self):
    first = self._settle(4.7, 0.047, 0.070)
    second = self._update(4.1, 0.040, 0.064, pressed=True)

    self.assertFalse(self.ext.bp_low_speed_curve_hold_active)
    self.assertLess(abs(second.path_angle), abs(first.path_angle))

  def test_lane_change_does_not_hold(self):
    self.ext.model = SimpleNamespace(
      orientationRate=SimpleNamespace(z=[0.0] * 33),
      meta=SimpleNamespace(laneChangeState=2, laneChangeDirection=0),
    )
    first = self._settle(4.7, 0.047, 0.070)
    second = self._update(4.1, 0.040, 0.064)

    self.assertFalse(self.ext.bp_low_speed_curve_hold_active)
    self.assertLess(abs(second.path_angle), abs(first.path_angle))

  def test_inactive_resets_hold_telemetry(self):
    self._settle(4.7, 0.047, 0.070)
    self._update(4.1, 0.040, 0.064)
    self.assertTrue(self.ext.bp_low_speed_curve_hold_active)

    result = self._update(4.1, 0.040, 0.064, lat_active=False)

    self.assertEqual(result.path_angle, 0.0)
    self.assertFalse(self.ext.bp_low_speed_curve_hold_active)


class TestMeasurementSelection(unittest.TestCase):
  """get_current_curvature must select by the CP_SP STEER_ANGLE_CURVATURE flag: yaw rate
  by default (stock ford.h angle_meas family), pinion angle via the vehicle model when
  the steering-angle curvature measurement is enabled (pinion ford.h angle_meas family).
  """

  V_EGO = 15.0

  def test_default_is_yaw_rate(self):
    ext, _ = _pinion_harness(flag=False)
    cs = _CS(vEgoRaw=self.V_EGO, yawRate=0.75, steeringAngleDeg=30.0)
    self.assertFalse(ext.bp_pinion_curvature_enabled)
    self.assertAlmostEqual(ext.get_current_curvature(cs), -0.75 / self.V_EGO)

  def test_flag_selects_pinion_vehicle_model(self):
    from opendbc.car.vehicle_model import VehicleModel
    ext, CP = _pinion_harness(flag=True)
    cs = _CS(vEgoRaw=self.V_EGO, yawRate=0.75, steeringAngleDeg=30.0)
    self.assertTrue(ext.bp_pinion_curvature_enabled)
    expected = -VehicleModel(CP).calc_curvature(math.radians(30.0), self.V_EGO, 0.0)
    self.assertAlmostEqual(ext.get_current_curvature(cs), expected)
    self.assertNotAlmostEqual(ext.get_current_curvature(cs), -0.75 / self.V_EGO)


class TestAngleParams(unittest.TestCase):
  def setUp(self):
    self.ext = _Harness(_explorer_cp())

  def test_high_speed_dampening_preserves_platform_gain(self):
    CP = _explorer_cp()
    CP.carFingerprint = CAR.FORD_F_150_MK14
    ext = _Harness(CP)
    ext.update_angle_params(_FakeParams({"FordHighSpeedDampening_ang": b"1.12"}))
    self.assertAlmostEqual(ext.path_angle_gain_lowC_highV, 0.95)
    self.assertAlmostEqual(ext.user_dampening_factor, 1.12)

  def test_high_speed_dampening_multiplies_low_curvature_high_speed_gain(self):
    self.ext.update_angle_params(_FakeParams({"FordHighSpeedDampening_ang": b"1.12"}))
    cs = _CS(vEgoRaw=26.82, vEgo=26.82)
    self.ext.update_angle_strategy(_CC(), cs, _Actuators(), self.ext.CP)
    self.assertAlmostEqual(
      self.ext.low_gain_calc,
      self.ext.path_angle_gain_lowC_highV * self.ext.user_dampening_factor,
    )

  def test_high_speed_dampening_is_clamped(self):
    for raw_value, expected in ((b"0.10", 0.25), (b"1.50", 1.25)):
      with self.subTest(raw_value=raw_value):
        self.ext.update_angle_params(_FakeParams({"FordHighSpeedDampening_ang": raw_value}))
        self.assertAlmostEqual(self.ext.user_dampening_factor, expected)


class TestPathAngleBounds(unittest.TestCase):
  """The internal sign convention is negated before packing, so its limits must be mirrored."""

  def test_internal_bounds_mirror_wire_bounds(self):
    self.assertEqual(FORD_INTERNAL_PATH_ANGLE_MIN, -FORD_DBC_PATH_ANGLE_MAX)
    self.assertEqual(FORD_INTERNAL_PATH_ANGLE_MAX, -FORD_DBC_PATH_ANGLE_MIN)

  def test_internal_clip_maps_exactly_into_wire_range(self):
    cases = (
      (-1.0, FORD_DBC_PATH_ANGLE_MAX),
      (FORD_INTERNAL_PATH_ANGLE_MIN, FORD_DBC_PATH_ANGLE_MAX),
      (FORD_INTERNAL_PATH_ANGLE_MAX, FORD_DBC_PATH_ANGLE_MIN),
      (1.0, FORD_DBC_PATH_ANGLE_MIN),
    )
    for internal, expected_wire in cases:
      with self.subTest(internal=internal):
        wire = -clip_ford_path_angle_internal(internal)
        self.assertAlmostEqual(wire, expected_wire)
        self.assertGreaterEqual(wire, FORD_DBC_PATH_ANGLE_MIN)
        self.assertLessEqual(wire, FORD_DBC_PATH_ANGLE_MAX)

  def test_wire_guard_prevents_unsigned_dbc_wrap(self):
    self.assertEqual(clip_ford_path_angle_wire(-1.0), FORD_DBC_PATH_ANGLE_MIN)
    self.assertEqual(clip_ford_path_angle_wire(1.0), FORD_DBC_PATH_ANGLE_MAX)

  def test_classic_can_builder_clips_wire_value(self):
    packer = _CapturePacker()
    fordcan_ext.create_lat_ctl_msg(
      packer, SimpleNamespace(main=0), True, 2, 1, 0.0, -1.0, 0.0, 0.0,
    )
    self.assertEqual(packer.calls[-1][2]["LatCtlPath_An_Actl"], FORD_DBC_PATH_ANGLE_MIN)

  def test_canfd_builder_clips_wire_value(self):
    packer = _CapturePacker()
    fordcan_ext.create_lat_ctl2_msg(
      packer, SimpleNamespace(main=0), 1, 2, 1, 0.0, 1.0, 0.0, 0.0, 0,
    )
    self.assertEqual(packer.calls[-1][2]["LatCtlPath_An_Actl"], FORD_DBC_PATH_ANGLE_MAX)


class TestInitializeFord(unittest.TestCase):
  def test_safety_param_stays_a_plain_int(self):
    """card serializes CP_SP to capnp, which rejects enum subclasses of int -- an
    IntFlag-typed safetyParam crashed card on-device. Pin the exact type."""
    from opendbc.sunnypilot.car.interfaces import _initialize_ford
    CP = structs.CarParams()
    CP.brand = 'ford'
    CP.carFingerprint = 'FORD_EXPLORER_MK6'
    CP_SP = structs.CarParamsSP()
    _initialize_ford(CP, CP_SP, {"FordPrefSteerAngleCurvature": True})
    self.assertEqual(CP_SP.safetyParam, 0xb)  # flag | (explorer index 5 << 1)
    self.assertIs(type(CP_SP.safetyParam), int)


if __name__ == '__main__':
  unittest.main()
