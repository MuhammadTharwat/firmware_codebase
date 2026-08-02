#!/bin/bash
source ../../RTOS/sdk-zephyr/zephyr-env.sh
export GNUARMEMB_TOOLCHAIN_PATH=/opt/arm-gnu-toolchain-15.2.rel1-x86_64-arm-none-eabi/
export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
# Now run your standard cmake step:
cmake -GNinja -DBOARD=$1 -BBuild

ninja -C ./Build/
