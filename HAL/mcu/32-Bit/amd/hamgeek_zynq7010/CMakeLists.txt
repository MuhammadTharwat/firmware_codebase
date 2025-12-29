cmake_minimum_required (VERSION 3.8)
 
project(hamgeek_zynq_7010_sdr)

message(STATUS "OCRAM Build")
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/lscript_ocram.ld)

						
include(${CMAKE_CURRENT_SOURCE_DIR}/hamgeek_zynq7010.cmake)

set(ZYNQ700_BSP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_2/src)
set(ZYNQ7000_FILES 
                ${ZYNQ700_BSP_DIR}/arm/cortexa9/gcc/xil-crt0.S
                ${ZYNQ700_BSP_DIR}/arm/cortexa9/gcc/boot.S
                ${ZYNQ700_BSP_DIR}/arm/cortexa9/gcc/asm_vectors.S
                ${ZYNQ700_BSP_DIR}/xtime_l.c
                ${ZYNQ700_BSP_DIR}/xil_exception.c
                ${ZYNQ700_BSP_DIR}/vectors.c
                ${ZYNQ700_BSP_DIR}/translation_table.S
					)

set(ZYNQ7000_INCLUDE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/standalone_bsp/zynq_platform/export/zynq_platform/sw/zynq_platform/standalone_domain/bspinclude/include

                    )


set_source_files_properties(${ZYNQ7000_FILES} PROPERTIES COMPILE_FLAGS "-Wno-unused-parameter -Wno-maybe-uninitialized")

add_library(${PROJECT_NAME} STATIC ${ZYNQ7000_FILES} 
                                    ./bsp_led.cpp
                                    ./bsp_uart.cpp
                                    ./bsp_spi.cpp
                                    ./bsp_sys.cpp
                                    )

target_include_directories (${PROJECT_NAME} PRIVATE ${ZYNQ7000_INCLUDE_DIR}
                                                    ${CMAKE_CURRENT_SOURCE_DIR}
                                                    )

target_include_directories (${PROJECT_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../bsp/v1
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../common
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../utility/dbg_log)


target_compile_definitions(${PROJECT_NAME} PRIVATE  )

target_compile_definitions(${PROJECT_NAME} PUBLIC  )

##### Link Baremetal OSAL
if(NOT TARGET RTOS_AL)
add_subdirectory(../../../../../RTOS/RTOS_OSAL/Baremetal_implementation ./Baremetal_implementation)
target_link_libraries(${PROJECT_NAME} PUBLIC RTOS_AL)
endif() 
