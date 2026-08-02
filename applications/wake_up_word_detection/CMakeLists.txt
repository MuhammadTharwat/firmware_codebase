# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)


set(ENV{ZEPHYR_BASE} ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/sdk-zephyr)

set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/nRF52/dynastream_nRF52)

set(ZEPHYR_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/hal_nordic/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/cmsis/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/CMSIS_6/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/tflite-micro/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/cmsis-nn/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/cmsis-dsp)


find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(Wake-up-word-detection LANGUAGES C CXX) 

target_sources(app PRIVATE main_thread/main.cpp)


#### Link ETL library
if(NOT TARGET etl)
# ETL includes GNUInstallDirs, which cannot infer a libdir when cross-compiling.
# ETL is header-only and never installed here, so the value is inert; setting it
# just takes GNUInstallDirs down its non-warning path.
set(CMAKE_INSTALL_LIBDIR "lib")
add_subdirectory(../../utility/etl ./etl)
endif()
target_link_libraries(app PRIVATE etl::etl)

target_compile_options(app PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

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