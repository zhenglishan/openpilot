import pytest

from openpilot.common.params import Params
from openpilot.system.updated.updated import Updater, get_agnos_update_files


@pytest.mark.parametrize(("device_type", "expected"), [
  ("tici", ("sunnypilot/system/hardware/c3/launch_env.sh", "sunnypilot/system/hardware/c3/agnos.json")),
  ("tizi", ("launch_env.sh", "system/hardware/tici/agnos.json")),
  ("mici", ("launch_env.sh", "system/hardware/tici/agnos.json")),
])
def test_agnos_update_files(device_type, expected):
  assert get_agnos_update_files(device_type) == expected


@pytest.mark.parametrize(("device_type", "branch", "expected"), [
  ("tizi", "release3", "release-tizi"),
  ("tizi", "release3-staging", "release-tizi-staging"),
  ("mici", "release3", "release-mici"),
  ("mici", "release3-staging", "release-mici-staging"),
])
def test_target_branch_migration_from_current_branch(mocker, device_type, branch, expected):
  params = Params()
  params.remove("UpdaterTargetBranch")

  mocker.patch("openpilot.system.updated.updated.HARDWARE.get_device_type", return_value=device_type)
  mocker.patch.object(Updater, "get_branch", return_value=branch)

  assert Updater().target_branch == expected


@pytest.mark.parametrize(("device_type", "branch", "expected"), [
  ("tizi", "release3", "release-tizi"),
  ("tizi", "release3-staging", "release-tizi-staging"),
  ("mici", "release3", "release-mici"),
  ("mici", "release3-staging", "release-mici-staging"),
])
def test_target_branch_migration_from_param(mocker, device_type, branch, expected):
  params = Params()
  params.put("UpdaterTargetBranch", branch, block=True)

  mocker.patch("openpilot.system.updated.updated.HARDWARE.get_device_type", return_value=device_type)

  try:
    assert Updater().target_branch == expected
  finally:
    params.remove("UpdaterTargetBranch")
