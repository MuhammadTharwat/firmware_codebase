## Check for Linker Script
if(NOT DEFINED LINKER_SCRIPT)
message(FATAL_ERROR "No linker script defined")
endif(NOT DEFINED LINKER_SCRIPT)

## Check for Optimization Level 
if(NOT DEFINED OPTIMIZATION_LEVEL)
set(OPTIMIZATION_LEVEL 			-Os)
endif()

## Check for Debug Information
if(NOT DEFINED DEBUG_INFORMATION_LEVEL)
set(DEBUG_INFORMATION_LEVEL 	-g3)
endif()

## Check for Application Specific Flags
if(NOT DEFINED APP_SPECIFIC_FLAGS)
	message( SEND_ERROR	"Define App Specific Configuration (APP_SPECIFIC_FLAGS)" )
endif()

#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------
set(OBJECT_GEN_FLAGS "${OPTIMIZATION_LEVEL} ${DEBUG_INFORMATION_LEVEL} ${APP_SPECIFIC_FLAGS} -DCUSTOM_PRINTF_LIB")

string(APPEND OBJECT_GEN_FLAGS " -Wall -Wformat-security -Wunused-parameter -Werror -Wformat -Wformat-security -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -ffreestanding -fno-builtin")
string(APPEND OBJECT_GEN_FLAGS " -ffunction-sections -fdata-sections ")

set(CMAKE_C_FLAGS "${OBJECT_GEN_FLAGS} -std=gnu11 -fno-strict-aliasing -fshort-enums " CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} -std=c++17 -fno-exceptions -fno-threadsafe-statics" CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS} -x assembler-with-cpp " CACHE INTERNAL "ASM Compiler options")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -nostdlib -ffreestanding -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")
link_libraries(gcc c m)