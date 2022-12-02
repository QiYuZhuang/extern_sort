cmake_minimum_required(VERSION 3.21)
project(extern_sort CXX)

set(CMAKE_C_STANDARD 17)

add_executable(extern_sort main.cpp load_buffer.cpp load_buffer.h temp_row.h)