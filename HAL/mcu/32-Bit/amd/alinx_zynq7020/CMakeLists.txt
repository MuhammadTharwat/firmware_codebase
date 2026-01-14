cmake_minimum_required (VERSION 3.8)
 
project(hamgeek_zynq_7010_sdr)

message(STATUS "OCRAM Build")
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/lscript_ocram.ld)

						
include(${CMAKE_CURRENT_SOURCE_DIR}/alinx_zynq7020.cmake)

set(ZYNQ700_BSP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc)
set(ZYNQ7000_FILES 
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/arm/cortexa9/gcc/xil-crt0.S
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/arm/cortexa9/gcc/boot.S
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/arm/cortexa9/gcc/asm_vectors.S
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/xtime_l.c
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/xil_exception.c
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/vectors.c
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/xil_assert.c
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/xplatform_info.c
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/translation_table.S
                ${ZYNQ700_BSP_DIR}/standalone_v9_0/src/_exit.c
                ${ZYNQ700_BSP_DIR}/gpiops_v3_12/src/xgpiops_g.c
                ${ZYNQ700_BSP_DIR}/gpiops_v3_12/src/xgpiops.c
                ${ZYNQ700_BSP_DIR}/gpiops_v3_12/src/xgpiops_hw.c
                ${ZYNQ700_BSP_DIR}/gpiops_v3_12/src/xgpiops_sinit.c
                ${ZYNQ700_BSP_DIR}/gpiops_v3_12/src/xgpiops_intr.c
                ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/hw/ps7_init_gpl.c
					)

set(ZYNQ7000_INCLUDE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/export/zynq_platform/sw/zynq_platform/standalone_domain/bspinclude/include
                            ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/hw

                    )


add_library(${PROJECT_NAME} OBJECT ${ZYNQ7000_FILES} 
                                    ./bsp_led.cpp
                                    ./bsp_uart.cpp
                                    ./bsp_io.cpp
                                    ./bsp_sys.cpp
                                    )

target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/export/zynq_platform/sw/zynq_platform/standalone_domain/bsplib/lib/libxil.a)
target_include_directories (${PROJECT_NAME} PRIVATE ${ZYNQ7000_INCLUDE_DIR}
                                                    )

target_include_directories (${PROJECT_NAME}  PUBLIC ${ZYNQ7000_INCLUDE_DIR}
                                                    ${CMAKE_CURRENT_SOURCE_DIR}
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../bsp/v1
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../common
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../utility/dbg_log)


target_compile_definitions(${PROJECT_NAME} PRIVATE  )

target_compile_definitions(${PROJECT_NAME} PUBLIC  )

##### Link Baremetal OSAL
if(NOT TARGET RTOS_AL)
add_subdirectory(../../../../../RTOS/RTOS_OSAL/Baremetal_implementation ./Baremetal_implementation)
target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_AL)
endif() 
