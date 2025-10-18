cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE "/home/muhammad/NCD_Common/toolchain-arm-none-eabi.cmake")
set(PROJECT_NAME Blinky)

project(${PROJECT_NAME} C CXX ASM)

set(EXECUTABLE ${PROJECT_NAME}.elf)

####################################SOURCE FILES##########################################
set(SOURCE_FILES ./Blinky_Demo.c
../standalone_bsp/zynq_platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_2/src/arm/cortexa9/gcc/xil-crt0.S
../standalone_bsp/zynq_platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_2/src/arm/cortexa9/gcc/boot.S
                )

add_executable(${EXECUTABLE} ${SOURCE_FILES})

############################### Define Optimization Level ##################################
set(OPTIMIZATION_LEVEL 			-Os)

############################### Define Debug Information Level #############################
set(DEBUG_INFORMATION_LEVEL 	-g3)
############################### App Specific Flags ##################
set(APP_SPECIFIC_FLAGS		"")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -ffunction-sections -fdata-sections -lc -lm -nostdlib -ffreestanding -T ${CMAKE_CURRENT_SOURCE_DIR}/../lscript_ocram.ld -Wl,--gc-sections")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--gc-sections -ffunction-sections -fdata-sections -g3 -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -ffreestanding -fno-builtin -Wall -Os")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard")
target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} 	PRIVATE  )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../standalone_bsp/zynq_platform/export/zynq_platform/sw/zynq_platform/standalone_domain/bspinclude/include
)

target_link_libraries(${EXECUTABLE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../standalone_bsp/zynq_platform/export/zynq_platform/sw/zynq_platform/standalone_domain/bsplib/lib/libxil.a gcc c m)

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE})
