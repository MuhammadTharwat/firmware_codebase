source ./venv/bin/activate

export ZEPHYR_BASE=/home/muhammad/firmware_codebase/RTOS/zephyr

# Now run your standard cmake step:
cmake -GNinja -DBOARD=nrf52833dk/nrf52833 -BBuild -DZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb -DGNUARMEMB_TOOLCHAIN_PATH=/home/muhammad/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux/gcc-arm-none-eabi-10.3-2021.10

ninja -C ./Build/
