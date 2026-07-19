# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)


set(ENV{ZEPHYR_BASE} ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/sdk-zephyr)

set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/nRF52/dynastream_nRF52)

set(ZEPHYR_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/hal_nordic/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/cmsis/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/CMSIS_6/)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(Blinky_example)

target_sources(app PRIVATE main_thread/main.c
                           ui_thread/ui_thread.c)


target_include_directories(app PRIVATE ui_thread/)

add_custom_target(copy_artifacts ALL
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/zephyr/zephyr.hex
        ${PROJECT_BINARY_DIR}/zephyr/${CMAKE_PROJECT_NAME}-${BOARD}.hex

    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/zephyr/zephyr.elf
        ${PROJECT_BINARY_DIR}/zephyr/${CMAKE_PROJECT_NAME}-${BOARD}.elf
)

add_dependencies(copy_artifacts zephyr_final)