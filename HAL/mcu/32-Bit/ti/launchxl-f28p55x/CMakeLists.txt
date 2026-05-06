cmake_minimum_required (VERSION 3.15)
 
project(LAUNCHXL_F28P55X)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker.cmd)
include(${CMAKE_CURRENT_SOURCE_DIR}/launchxl-f28p55x.cmake)

set(TI_SDK_FILES 
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/adc.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/fsi.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/aes.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/gpio.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/asysctl.c   
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/hrpwm.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/cla.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/i2c.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/clb.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/interrupt.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/cmpss.c     
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/lin.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/cputimer.c  
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/mcan.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/dac.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/memcfg.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/dcc.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/pga.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/dcsm.c      
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/pmbus.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/dma.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/sci.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/ecap.c      
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/spi.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/epg.c       
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/sysctl.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/epwm.c      
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/usb.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/eqep.c      
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/version.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/erad.c      
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/xbar.c
                ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/flash.c
                ../c2000ware-core-sdk/device_support/f28p55x/headers/source/f28p55x_globalvariabledefs.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/device.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_adc.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_cputimers.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_defaultisr.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_dma.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_epwm.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_gpio.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_npu.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_piectrl.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_pievect.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_sysctrl.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_tempsensorconv.c
                ../c2000ware-core-sdk/device_support/f28p55x/common/source/f28p55x_codestartbranch.asm
				)

set(TI_SDK_INCLUDE_DIR  ../c2000ware-core-sdk/driverlib/f28p55x/driverlib
                        ../c2000ware-core-sdk/driverlib/f28p55x/driverlib/inc
                        ../c2000ware-core-sdk/device_support/f28p55x/headers/include
                        ../c2000ware-core-sdk/device_support/f28p55x/common/include
                    )


set_source_files_properties(${TI_SDK_FILES} PROPERTIES COMPILE_FLAGS "--diag_suppress=179,552")

add_library(${PROJECT_NAME} STATIC ${TI_SDK_FILES} 
                                    ./bsp_led.cpp
                                    ./bsp_uart.cpp
                                    ./bsp_spi.cpp
                                    ./bsp_io.cpp
                                    ./bsp_sys.cpp
                                    )


target_include_directories (${PROJECT_NAME} PRIVATE ${TI_SDK_INCLUDE_DIR}
                                                    )

target_include_directories (${PROJECT_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../bsp/v1
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../common
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../utility/dbg_log)


target_link_libraries(${PROJECT_NAME}  PRIVATE	$ENV{CG_TOOL_ROOT}/lib/rts2800_fpu32_eabi.lib
                                                )

target_compile_definitions(${PROJECT_NAME} PRIVATE  )

target_compile_definitions(${PROJECT_NAME} PUBLIC  )

##### Link Baremetal OSAL
if(NOT TARGET RTOS_AL)
add_subdirectory(../../../../../RTOS/RTOS_OSAL/Baremetal_implementation ./Baremetal_implementation)
target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_AL)
endif() 
