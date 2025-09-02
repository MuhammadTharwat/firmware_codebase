cmake_minimum_required (VERSION 3.8)
 
project(diagnostic_log)

set(${PROJECT_NAME}_SOURCE 	${CMAKE_CURRENT_SOURCE_DIR}/diagnostic_log.cpp
													)
 
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE})

target_include_directories (${PROJECT_NAME} 	PRIVATE 	../../HAL/mcu/bsp/v1
															../../common
															../../RTOS/RTOS_OSAL)


target_include_directories (${PROJECT_NAME} 	PUBLIC 		${CMAKE_CURRENT_SOURCE_DIR}
															)
