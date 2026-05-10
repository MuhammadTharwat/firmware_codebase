cmake_minimum_required(VERSION 3.14)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")

set(PROJECT_NAME Blinky-launchxl-f28p55x)

project(${PROJECT_NAME} C CXX ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

####################################SOURCE FILES##########################################
set(SOURCE_FILES ./Blinky.cpp)

add_executable(${EXECUTABLE} ${SOURCE_FILES})

############################### Define Optimization Level ##################################
set(OPTIMIZATION_LEVEL 			-Os)

############################### Define Debug Information Level #############################
set(DEBUG_INFORMATION_LEVEL 	-g3)
############################### App Specific Flags ##################
set(APP_SPECIFIC_FLAGS		"")

target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} 	PRIVATE  )

add_subdirectory(../ ./launchxl-f28p55x)
target_link_libraries(${EXECUTABLE} PUBLIC LAUNCHXL_F28P55X)

add_subdirectory(../../../../../../utility/dbg_log ./diagnostic_log)
target_include_directories (diagnostic_log	PRIVATE ../../../../../../RTOS/RTOS_OSAL/Baremetal_implementation
                                                ../)
target_link_libraries(${EXECUTABLE} PUBLIC diagnostic_log)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_GENERATE_HEX} ${EXECUTABLE} -O ${PROJECT_NAME}.hex) 

