set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR "Nios V/m")
set(CMAKE_CROSSCOMPILING True)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_AR riscv32-unknown-elf-ar)
set(CMAKE_ASM_COMPILER riscv32-unknown-elf-gcc)
set(CMAKE_C_COMPILER riscv32-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER riscv32-unknown-elf-g++)

set(ToolchainPrefix riscv32-unknown-elf- CACHE STRING "Toolchain prefix." FORCE)

set(ToolchainObjdump riscv32-unknown-elf-objdump CACHE STRING "Objdump executable." FORCE)
set(ToolchainObjdumpFlags -Sdtx CACHE STRING "Objdump flags." FORCE)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Defaulting build type to Debug.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

set(OBJECT_GEN_FLAGS "${APP_SPECIFIC_FLAGS}")

string(APPEND OBJECT_GEN_FLAGS " -Os -DALT_SINGLE_THREADED -Wall -Wformat-security -Wunused-parameter  -Werror -Wformat -Wformat-security")
string(APPEND OBJECT_GEN_FLAGS " -ffunction-sections -fdata-sections -fstack-protector-strong -march=rv32i -mabi=ilp32")
string(APPEND OBJECT_GEN_FLAGS " -DALT_LOG_FLAGS=0 -DALT_NO_CLEAN_EXIT -DALT_NO_EXIT -DALT_USE_DIRECT_DRIVERS -D__hal__")


set(CMAKE_C_FLAGS "${OBJECT_GEN_FLAGS} -std=gnu11 " CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} -std=c++17 -fno-exceptions -fno-threadsafe-statics -fno-rtti" CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS} -Wa,-gdwarf2 " CACHE INTERNAL "ASM Compiler options")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections --specs=nosys.specs -Wl,--defsym,exit=_exit -Wl,--gc-sections -march=rv32i -mabi=ilp32 -nostdlib" CACHE INTERNAL "Linker options")
set(CMAKE_LINK_LIB "-lm -lc -lgcc")