## Check for Linker Script
if(NOT DEFINED LINKER_SCRIPT)
message(FATAL_ERROR "No linker script defined")
endif(NOT DEFINED LINKER_SCRIPT)

## Check for Application Specific Flags
if(NOT DEFINED APP_SPECIFIC_FLAGS)
	message( SEND_ERROR	"Define App Specific Configuration (APP_SPECIFIC_FLAGS)" )
endif()

#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------

set(OBJECT_GEN_FLAGS "-D_FLASH --fp_mode=relaxed --silicon_version=28 --opt_level=off --abi=eabi -DCUSTOM_PRINTF_LIB -D__TMS320C28XX__ --diag_suppress=2873,2874,3195 --display_error_number --include_path=$ENV{CG_TOOL_ROOT}/include --preinclude=${CMAKE_CURRENT_LIST_DIR}/primitive_types_definition.h --preinclude=${CMAKE_CURRENT_LIST_DIR}/../c2000ware-core-sdk/driverlib/f28p55x/driverlib/inc/hw_types.h\
 --float_support=fpu32 --tmu_support=tmu1 --gen_func_subsections=on")

string(APPEND OBJECT_GEN_FLAGS "")


set(CMAKE_C_FLAGS "${OBJECT_GEN_FLAGS} " CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} --c++03 " CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS}" CACHE INTERNAL "ASM Compiler options")

set(CMAKE_EXE_LINKER_FLAGS "--diag_suppress=10063 --rom_model --unused_section_elimination ${LINKER_SCRIPT} --entry_point code_start --stack_size=0x200 --heap_size=0x100 --map_file=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")