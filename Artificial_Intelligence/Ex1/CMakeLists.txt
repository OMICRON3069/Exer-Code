cmake_minimum_required(VERSION 3.10)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src ex1)

add_executable(Ex1 ${ex1})