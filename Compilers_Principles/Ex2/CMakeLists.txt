cmake_minimum_required(VERSION 3.10)
project(ooo0ooo)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src Source_main)

add_subdirectory(lib)

add_executable(oooctl ${Source_main})

target_link_libraries(oooctl ooo)