cmake_minimum_required(VERSION 3.14)

add_subdirectory(../ ./alinx_minimal_sys)

include(../bsp_hal/toolchain.cmake)

project(BootROM)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

set(EXECUTABLE ${PROJECT_NAME}.elf)

####################################SOURCE FILES##########################################
set(SOURCE_FILES ./BootROM.cpp)

add_executable(${EXECUTABLE} ${SOURCE_FILES})

############################### Define Optimization Level ##################################
set(OPTIMIZATION_LEVEL 			-Os)

############################### Define Debug Information Level #############################
set(DEBUG_INFORMATION_LEVEL 	-g)
############################### App Specific Flags ##################
set(APP_SPECIFIC_FLAGS		"-DDEBUG_MODE -DIAGNOSTIC_LOG")

target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} 	PRIVATE  )


target_link_libraries(${EXECUTABLE} PUBLIC alinx_minimal_sys)


target_link_libraries(${EXECUTABLE} PUBLIC alinx_minimal_sys
    PRIVATE
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map
        -T "${BspLinkerScript}" -nostdlib
        "${ExtraArchiveLibraries}"
)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${ToolchainPrefix}size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND elf2hex ${EXECUTABLE} -o ${PROJECT_NAME}.hex -b 0x20000000 -w 32 -e 0x20003FFF -r 4
        COMMAND ${ToolchainPrefix}objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
