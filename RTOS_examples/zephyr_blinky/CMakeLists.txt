# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)

# list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/nRF52/dynastream_nRF52)

set(ZEPHYR_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/hal_nordic/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/cmsis/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/CMSIS_6/)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)
target_sources(app PRIVATE src/main.c)
