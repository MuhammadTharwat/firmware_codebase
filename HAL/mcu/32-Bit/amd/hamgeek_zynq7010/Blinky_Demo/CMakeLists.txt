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
set(APP_SPECIFIC_FLAGS		"")

add_subdirectory(../ ./hamgeek_zynq_7010_sdr)
target_link_libraries(${EXECUTABLE} PUBLIC hamgeek_zynq_7010_sdr gcc c m)

target_compile_definitions(${EXECUTABLE} PRIVATE)

target_include_directories (${EXECUTABLE} 	PRIVATE  )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${TOOLCHAIN_PREFIX}size ${EXECUTABLE})
