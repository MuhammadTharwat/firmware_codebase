source ../../RTOS/zephyr/zephyr-env.sh
export GNUARMEMB_TOOLCHAIN_PATH=/opt/gcc-arm-none-eabi-10.3-2021.10/
export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
# Now run your standard cmake step:
cmake -GNinja -DBOARD=$1 -BBuild

ninja -C ./Build/
