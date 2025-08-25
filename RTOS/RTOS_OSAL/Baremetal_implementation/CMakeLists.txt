cmake_minimum_required (VERSION 3.8)
 
project(RTOS_AL)


set(SOURCE_FILES 
					./mutex.cpp
					./semaphore.cpp
					./timer.cpp
					./queue.cpp
					./thread.cpp
					./rtos_al.cpp
					)
 
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories (${PROJECT_NAME} 	PRIVATE 	
													../../../common											
													)

target_include_directories (${PROJECT_NAME} 	PUBLIC 
													./
													../											
													)


