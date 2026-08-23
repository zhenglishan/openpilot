#!/usr/bin/env bash

export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1

export FPS=20

export QCOM_PRIORITY=12

# The original comma 3 has a DOS/STM32F4 panda on USB. AGNOS also exposes an
# unused spidev node, so explicitly prevent pandad from probing it as a C3X/H7.
export PANDA_USB_ONLY=1

# Keep slot B on the known-good AGNOS 18.4 while validating AGNOS 18.5 on slot A.
# This prevents a failed A-slot boot from causing an automatic A/B reboot loop.
if [ -z "$AGNOS_VERSION" ]; then
  C3_BOOT_SLOT="$(sudo abctl --boot_slot 2>/dev/null | tr -d '\r\n')"
  if [ "$C3_BOOT_SLOT" = "_a" ]; then
    export AGNOS_VERSION="18.5"
  else
    export AGNOS_VERSION="18.4"
  fi
fi

export STAGING_ROOT="/data/safe_staging"
