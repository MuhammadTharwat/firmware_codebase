source ./venv/bin/activate

source ../../RTOS/zephyr/zephyr-env.sh
export GNUARMEMB_TOOLCHAIN_PATH=/home/muhammad/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux/gcc-arm-none-eabi-10.3-2021.10
# Now run your standard cmake step:
cmake -GNinja -DBOARD=$1 -BBuild -DZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb

ninja -C ./Build/
