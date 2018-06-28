cmake_minimum_required(VERSION 3.10)
project(Ex2)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(Ex4 MainD)

add_executable(Ex2 ${MainD})