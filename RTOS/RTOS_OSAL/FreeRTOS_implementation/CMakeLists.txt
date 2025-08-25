cmake_minimum_required (VERSION 3.8)
project(RTOS_AL)

set(SOURCE_FILES 
					./mutex.cpp
					./semaphore.cpp
					./timer.cpp
					./thread.cpp
					./queue.cpp
					./rtos_al.cpp
					./rtos_err_map.cpp
					)
					
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories (${PROJECT_NAME} 	PRIVATE 	
													../../FreeRTOS-Kernel/include																														
													../../../common
													../../../utility/dbg_log
													../../../common/SysPwr									
													)

target_include_directories (${PROJECT_NAME} 	PUBLIC 	
													./
													../											
													)
													
##### Link FREERTOS
if(NOT TARGET freertos_kernel)
add_subdirectory(../../FreeRTOS-Kernel ./freertos_kernel)
endif() 

target_include_directories(freertos_kernel PUBLIC ../../../common
												  ../../../utility/dbg_log
												  ../../../common/SysPwr)
target_link_libraries(${PROJECT_NAME} PUBLIC freertos_kernel)