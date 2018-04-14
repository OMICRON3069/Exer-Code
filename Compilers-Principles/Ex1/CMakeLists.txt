cmake_minimum_required(VERSION 3.10)
project(Ding)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src Source_main)

add_subdirectory(lib)

add_executable(dictl ${Source_main})

target_link_libraries(dictl ding)