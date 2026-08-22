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

#### tflite-micro's signal-library kernels.
set(TFLM ${CMAKE_CURRENT_SOURCE_DIR}/../../HAL/mcu/32-Bit/Nordic/tflite-micro)
target_sources(app PRIVATE
    ${TFLM}/signal/micro/kernels/energy.cc
    ${TFLM}/signal/micro/kernels/fft_auto_scale_common.cc
    ${TFLM}/signal/micro/kernels/fft_auto_scale_kernel.cc
    ${TFLM}/signal/micro/kernels/filter_bank.cc
    ${TFLM}/signal/micro/kernels/filter_bank_log.cc
    ${TFLM}/signal/micro/kernels/filter_bank_spectral_subtraction.cc
    ${TFLM}/signal/micro/kernels/filter_bank_square_root.cc
    ${TFLM}/signal/micro/kernels/filter_bank_square_root_common.cc
    ${TFLM}/signal/micro/kernels/pcan.cc
    ${TFLM}/signal/src/energy.cc
    ${TFLM}/signal/src/fft_auto_scale.cc
    ${TFLM}/signal/src/filter_bank.cc
    ${TFLM}/signal/src/filter_bank_log.cc
    ${TFLM}/signal/src/filter_bank_spectral_subtraction.cc
    ${TFLM}/signal/src/filter_bank_square_root.cc
    ${TFLM}/signal/src/log.cc
    ${TFLM}/signal/src/max_abs.cc
    ${TFLM}/signal/src/msb_32.cc
    ${TFLM}/signal/src/msb_64.cc
    ${TFLM}/signal/src/pcan_argc_fixed.cc
    ${TFLM}/signal/src/square_root_32.cc
    ${TFLM}/signal/src/square_root_64.cc)


target_sources(app PRIVATE main_thread/main.cpp
                            testdata/no_30ms_audio_data.cc
                            testdata/yes_30ms_audio_data.cc
                            testdata/yes_1000ms_audio_data.cc
                            models/audio_model/audio_preprocessor_int8_model_data.cpp
                            models/micro_speech/micro_speech_quantized_model_data.cpp)


#### Link ETL library
if(NOT TARGET etl)
# ETL includes GNUInstallDirs, which cannot infer a libdir when cross-compiling.
# ETL is header-only and never installed here, so the value is inert; setting it
# just takes GNUInstallDirs down its non-warning path.
set(CMAKE_INSTALL_LIBDIR "lib")
add_subdirectory(../../utility/etl ./etl)
endif()
target_link_libraries(app PRIVATE etl::etl)

target_include_directories(app PRIVATE  ui_thread/
                                        models/audio_model/
                                        models/micro_speech/
                                        testdata/)

add_custom_target(copy_artifacts ALL
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/zephyr/zephyr.hex
        ${PROJECT_BINARY_DIR}/zephyr/${CMAKE_PROJECT_NAME}-${BOARD}.hex

    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/zephyr/zephyr.elf
        ${PROJECT_BINARY_DIR}/zephyr/${CMAKE_PROJECT_NAME}-${BOARD}.elf
)

add_dependencies(copy_artifacts zephyr_final)