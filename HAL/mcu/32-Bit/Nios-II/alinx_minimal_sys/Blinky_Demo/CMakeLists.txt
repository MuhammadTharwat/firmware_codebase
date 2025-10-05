cmake_minimum_required(VERSION 3.14)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")

set(PROJECT_NAME BootROM-alinx-minimal-sys)

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

add_subdirectory(../ ./alinx_minimal_sys)
target_link_libraries(${EXECUTABLE} PUBLIC ALINX_MINIMAL_SYS)

add_subdirectory(../../../../../../utility/dbg_log ./diagnostic_log)
target_include_directories (diagnostic_log	PRIVATE ../../../../../../RTOS/RTOS_OSAL/Baremetal_implementation
                                                ../)
target_link_libraries(${EXECUTABLE} PUBLIC diagnostic_log)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE}
        COMMAND ${TOOLCHAIN_PREFIX}objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND ${TOOLCHAIN_PREFIX}objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
        COMMAND ${TOOLCHAIN_PREFIX}objcopy -I binary -O ihex --adjust-vma=0x400000 ${PROJECT_NAME}.bin ${PROJECT_NAME}-bootrom-load.hex)
