cmake_minimum_required(VERSION 3.14)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")
project(BootROM C CXX ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

####################################SOURCE FILES##########################################
set(SOURCE_FILES ./BootROM.cpp)

add_executable(${EXECUTABLE} ${SOURCE_FILES})

############################### Define Optimization Level ##################################
set(OPTIMIZATION_LEVEL 			-Os)

############################### Define Debug Information Level #############################
set(DEBUG_INFORMATION_LEVEL 	-g3)
############################### App Specific Flags ##################
set(APP_SPECIFIC_FLAGS		"-DDIAGNOSTIC_LOG")

target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} 	PRIVATE  )

add_subdirectory(../ ./alinx_minimal_sys)
target_link_libraries(${EXECUTABLE} PUBLIC ALINX_MINIMAL_SYS)

add_subdirectory(../../../../../memory/m25p64 ./m25p64)
target_include_directories (m25p64	PRIVATE ../../../../../../RTOS/RTOS_OSAL/Baremetal_implementation
                                                ../)
target_link_libraries(${EXECUTABLE} PUBLIC m25p64)

add_subdirectory(../../../../../../utility/dbg_log ./diagnostic_log)
target_include_directories (diagnostic_log	PRIVATE ../../../../../../RTOS/RTOS_OSAL/Baremetal_implementation
                                                ../)
target_link_libraries(${EXECUTABLE} PUBLIC diagnostic_log)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE})
