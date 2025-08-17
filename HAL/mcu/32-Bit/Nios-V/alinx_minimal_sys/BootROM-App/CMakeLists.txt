cmake_minimum_required(VERSION 3.14)

add_subdirectory(../bsp_hal bsp_hal)

include(../bsp_hal/toolchain.cmake)

project(BootROM)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

add_executable(BootROM.elf)

target_sources(BootROM.elf
    PRIVATE
        ./BootROM.cpp
)

target_include_directories(BootROM.elf
    PRIVATE
    PUBLIC
)

target_link_libraries(BootROM.elf
    PRIVATE
        -T "${BspLinkerScript}" -nostdlib
        "${ExtraArchiveLibraries}"
        -Wl,--start-group "${BspLibraryName}" -lc -lstdc++ -lgcc -lm -Wl,--end-group
)

# Create objdump from ELF.
set(objdump BootROM.elf.objdump)
add_custom_command(
    OUTPUT "${objdump}"
    DEPENDS BootROM.elf
    COMMAND "${ToolchainObjdump}" "${ToolchainObjdumpFlags}" BootROM.elf >
            "${objdump}"
    COMMENT "Creating ${objdump}."
    VERBATIM
)
add_custom_target(create-objdump ALL DEPENDS "${objdump}")

# Print executable size
add_custom_command(TARGET BootROM.elf
        POST_BUILD
        COMMAND ${ToolchainPrefix}size BootROM.elf)
# Generate HEX file(s) from BootROM.elf using elf2hex tool.
# Note : If ECC Full is enabled, width of 39 is set for NiosV TCM. Otherwise, 32.
add_custom_command(
    OUTPUT "BootROM.hex"
    DEPENDS BootROM.elf
    COMMAND elf2hex BootROM.elf -o BootROM.hex -b 0x20000000 -w 32 -e 0x20003FFF -r 4
    COMMENT "Creating BootROM.hex."
    VERBATIM
)

