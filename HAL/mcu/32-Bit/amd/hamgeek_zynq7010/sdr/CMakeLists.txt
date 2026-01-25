cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")
set(PROJECT_NAME SDR)

project(${PROJECT_NAME} C CXX ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

####################################SOURCE FILES##########################################

set(ADI_FILES    ../no-OS/drivers/rf-transceiver/ad9361/ad9361.c
                ../no-OS/drivers/rf-transceiver/ad9361/ad9361_api.c
                ../no-OS/drivers/rf-transceiver/ad9361/ad9361_conv.c
                ../no-OS/drivers/rf-transceiver/ad9361/ad9361_util.c
                ../no-OS/drivers/axi_core/axi_adc_core/axi_adc_core.c
                ../no-OS/drivers/axi_core/axi_dac_core/axi_dac_core.c
                ../no-OS/drivers/axi_core/axi_dmac/axi_dmac.c
                ../no-OS/drivers/api/no_os_gpio.c
                ../no-OS/drivers/api/no_os_spi.c
                ../no-OS/drivers/api/no_os_irq.c
                ../no-OS/drivers/platform/xilinx/xilinx_axi_io.c
                ../no-OS/drivers/platform/xilinx/xilinx_delay.c
                ../no-OS/drivers/platform/xilinx/xilinx_irq.c
                ../no-OS/util/no_os_util.c
                ../no-OS/util/no_os_mutex.c
                ../no-OS/util/no_os_alloc.c
                )

set(SOURCE_FILES ./sdr_main.cpp
                ${ADI_FILES}
                )

add_executable(${EXECUTABLE} ${SOURCE_FILES})

target_include_directories (${EXECUTABLE}	PRIVATE ../no-OS/include
                                                        ../no-OS/drivers/rf-transceiver/ad9361
                                                        ../no-OS/drivers/axi_core/axi_adc_core
                                                        ../no-OS/drivers/axi_core/axi_dac_core
                                                        ../no-OS/drivers/axi_core/axi_dmac
                                                        ../no-OS/drivers/platform/xilinx
                                                        ../
                                                        ./)

set_source_files_properties(${ADI_FILES} PROPERTIES COMPILE_FLAGS "-Wno-unused-parameter")
############################### Define Optimization Level ##################################
set(OPTIMIZATION_LEVEL 			-Os)

############################### Define Debug Information Level #############################
set(DEBUG_INFORMATION_LEVEL 	-g3)
############################### App Specific Flags ##################
set(APP_SPECIFIC_FLAGS		"-DDIAGNOSTIC_LOG")

add_subdirectory(../ ./hamgeek_zynq_7010_sdr)
target_link_libraries(${EXECUTABLE} PUBLIC hamgeek_zynq_7010_sdr)

target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} PRIVATE  ../no-OS/include)

add_subdirectory(../../../../../../utility/dbg_log ./diagnostic_log)
target_include_directories (diagnostic_log	PRIVATE ../../../../../../RTOS/RTOS_OSAL/Baremetal_implementation
                                                        )
target_link_libraries(${EXECUTABLE} PUBLIC diagnostic_log)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE})
