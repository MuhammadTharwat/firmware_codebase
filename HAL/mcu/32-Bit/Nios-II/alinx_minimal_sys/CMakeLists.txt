cmake_minimum_required (VERSION 3.8)
 
project(ALINX_MINIMAL_SYS)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/bsp_hal/linker.x)
						
include(${CMAKE_CURRENT_SOURCE_DIR}/alinx_minimal_sys.cmake)

set(ALTERA_FILES 
                ./bsp_hal/alt_sys_init.c    
                ./bsp_hal/HAL/src/altera_nios2_gen2_irq.c
                ./bsp_hal/HAL/src/alt_usleep.c
                ./bsp_hal/HAL/src/alt_busy_sleep.c
                ./bsp_hal/HAL/src/alt_irq_vars.c
                ./bsp_hal/HAL/src/alt_icache_flush.c
                ./bsp_hal/HAL/src/alt_icache_flush_all.c
                ./bsp_hal/HAL/src/alt_dcache_flush.c
                ./bsp_hal/HAL/src/alt_dcache_flush_all.c
                ./bsp_hal/HAL/src/alt_dcache_flush_no_writeback.c
                ./bsp_hal/HAL/src/alt_ecc_fatal_exception.c
                ./bsp_hal/HAL/src/alt_instruction_exception_entry.c
                ./bsp_hal/HAL/src/alt_irq_register.c
                ./bsp_hal/HAL/src/alt_iic.c
                ./bsp_hal/HAL/src/alt_remap_cached.c
                ./bsp_hal/HAL/src/alt_remap_uncached.c
                ./bsp_hal/HAL/src/alt_uncached_free.c
                ./bsp_hal/HAL/src/alt_uncached_malloc.c
                ./bsp_hal/HAL/src/alt_do_ctors.c
                ./bsp_hal/HAL/src/alt_do_dtors.c
                ./bsp_hal/HAL/src/alt_gmon.c
                ./bsp_hal/HAL/src/alt_ecc_fatal_entry.S 
                ./bsp_hal/HAL/src/alt_exception_entry.S
                ./bsp_hal/HAL/src/alt_exception_trap.S
                ./bsp_hal/HAL/src/alt_exception_muldiv.S
                ./bsp_hal/HAL/src/alt_irq_entry.S
                ./bsp_hal/HAL/src/alt_software_exception.S
                ./bsp_hal/HAL/src/alt_mcount.S
                ./bsp_hal/HAL/src/alt_log_macro.S
                ./bsp_hal/HAL/src/crt0.S
                ./bsp_hal/HAL/src/alt_alarm_start.c
                ./bsp_hal/HAL/src/alt_close.c
                ./bsp_hal/HAL/src/alt_dev.c
                ./bsp_hal/HAL/src/alt_dev_llist_insert.c
                ./bsp_hal/HAL/src/alt_dma_rxchan_open.c
                ./bsp_hal/HAL/src/alt_dma_txchan_open.c
                ./bsp_hal/HAL/src/alt_environ.c
                ./bsp_hal/HAL/src/alt_env_lock.c
                ./bsp_hal/HAL/src/alt_errno.c
                ./bsp_hal/HAL/src/alt_execve.c
                ./bsp_hal/HAL/src/alt_exit.c
                ./bsp_hal/HAL/src/alt_fcntl.c
                ./bsp_hal/HAL/src/alt_fd_lock.c
                ./bsp_hal/HAL/src/alt_fd_unlock.c
                ./bsp_hal/HAL/src/alt_find_dev.c
                ./bsp_hal/HAL/src/alt_find_file.c
                ./bsp_hal/HAL/src/alt_flash_dev.c
                ./bsp_hal/HAL/src/alt_fork.c
                ./bsp_hal/HAL/src/alt_fs_reg.c
                ./bsp_hal/HAL/src/alt_fstat.c
                ./bsp_hal/HAL/src/alt_get_fd.c
                ./bsp_hal/HAL/src/alt_getchar.c
                ./bsp_hal/HAL/src/alt_getpid.c
                ./bsp_hal/HAL/src/alt_gettod.c
                ./bsp_hal/HAL/src/alt_iic_isr_register.c
                ./bsp_hal/HAL/src/alt_instruction_exception_register.c
                ./bsp_hal/HAL/src/alt_ioctl.c
                ./bsp_hal/HAL/src/alt_io_redirect.c
                ./bsp_hal/HAL/src/alt_irq_handler.c
                ./bsp_hal/HAL/src/alt_isatty.c
                ./bsp_hal/HAL/src/alt_kill.c
                ./bsp_hal/HAL/src/alt_link.c
                ./bsp_hal/HAL/src/alt_load.c
                ./bsp_hal/HAL/src/alt_log_printf.c
                ./bsp_hal/HAL/src/alt_lseek.c
                ./bsp_hal/HAL/src/alt_main.c
                ./bsp_hal/HAL/src/alt_malloc_lock.c
                ./bsp_hal/HAL/src/alt_open.c
                ./bsp_hal/HAL/src/alt_printf.c
                ./bsp_hal/HAL/src/alt_putchar.c
                ./bsp_hal/HAL/src/alt_putcharbuf.c
                ./bsp_hal/HAL/src/alt_putstr.c
                ./bsp_hal/HAL/src/alt_read.c
                ./bsp_hal/HAL/src/alt_release_fd.c
                ./bsp_hal/HAL/src/alt_rename.c
                ./bsp_hal/HAL/src/alt_sbrk.c
                ./bsp_hal/HAL/src/alt_settod.c
                ./bsp_hal/HAL/src/alt_stat.c
                ./bsp_hal/HAL/src/alt_tick.c
                ./bsp_hal/HAL/src/alt_times.c
                ./bsp_hal/HAL/src/alt_unlink.c
                ./bsp_hal/HAL/src/alt_wait.c
                ./bsp_hal/HAL/src/alt_write.c
					)

set(ALTERA_INCLUDE_DIR  ./bsp_hal
                        ./bsp_hal/HAL/inc
                        ./bsp_hal/HAL/inc/os
                        ./bsp_hal/HAL/inc/priv
                        ./bsp_hal/HAL/inc/sys
                        ./bsp_hal/drivers/inc
                    )


set_source_files_properties(${ALTERA_FILES} PROPERTIES COMPILE_FLAGS "-Wno-unused-parameter -Wno-maybe-uninitialized")

add_library(${PROJECT_NAME} STATIC ${ALTERA_FILES} 
                                    ./bsp_led.cpp
                                    ./bsp_uart.cpp
                                    ./bsp_spi.cpp
                                    ./bsp_io.cpp
                                    )

target_include_directories (${PROJECT_NAME} PRIVATE ${ALTERA_INCLUDE_DIR}
                                                    )

target_include_directories (${PROJECT_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
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
