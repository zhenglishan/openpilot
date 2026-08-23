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

# The C3-compatible image in agnos.json reports AGNOS 18.4 after boot.
if [ -z "$AGNOS_VERSION" ]; then
  export AGNOS_VERSION="18.4"
fi

export STAGING_ROOT="/data/safe_staging"
