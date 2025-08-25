cmake_minimum_required (VERSION 3.8)

add_subdirectory(./bsp_hal bsp_hal)

include(./bsp_hal/toolchain.cmake)

project(alinx_minimal_sys)



set(COMMON_SOURCE_FILES  ./bsp_led.cpp
                         ./bsp_sys.cpp
                         ./bsp_io.cpp
					)

add_library(${PROJECT_NAME} OBJECT ${COMMON_SOURCE_FILES})


target_include_directories (${PROJECT_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
													${CMAKE_CURRENT_SOURCE_DIR}/../../../bsp/v1
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../common)

target_compile_definitions(${PROJECT_NAME} PRIVATE  
                                                     )

target_link_libraries(${PROJECT_NAME}
PRIVATE
    "${ExtraArchiveLibraries}"
    -Wl,--start-group "${BspLibraryName}" -lc -lstdc++ -lgcc -lm -Wl,--end-group
)
                                                 