cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")
set(PROJECT_NAME Blinky)

project(${PROJECT_NAME} C CXX ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

####################################SOURCE FILES##########################################
set(SOURCE_FILES ./Blinky_Demo.cpp
                )

add_executable(${EXECUTABLE} ${SOURCE_FILES})

############################### Define Optimization Level ##################################
set(OPTIMIZATION_LEVEL 			-Os)

############################### Define Debug Information Level #############################
set(DEBUG_INFORMATION_LEVEL 	-g3)
############################### App Specific Flags ##################
set(APP_SPECIFIC_FLAGS		"-DDIAGNOSTIC_LOG")

add_subdirectory(../ ./hamgeek_zynq_7010_sdr)
target_link_libraries(${EXECUTABLE} PUBLIC hamgeek_zynq_7010_sdr)

target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} 	PRIVATE  )

add_subdirectory(../../../../../../utility/dbg_log ./diagnostic_log)
target_include_directories (diagnostic_log	PRIVATE ../../../../../../RTOS/RTOS_OSAL/Baremetal_implementation
                                                ../)
target_link_libraries(${EXECUTABLE} PUBLIC diagnostic_log)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE})
