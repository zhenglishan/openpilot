#!/usr/bin/env bash

export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1

export FPS=20

export QCOM_PRIORITY=12

# The C3-compatible image in agnos.json reports AGNOS 18.4 after boot.
if [ -z "$AGNOS_VERSION" ]; then
  export AGNOS_VERSION="18.4"
fi

export STAGING_ROOT="/data/safe_staging"
