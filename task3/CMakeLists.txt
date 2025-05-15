cmake_minimum_required(VERSION 3.10.0)
project(task3 VERSION 0.1.0 LANGUAGES C CXX)

set(HEADER_FILES ../task2/typelist.h typemap.h)

include_directories(PUBLIC ../task2)

add_executable(task3 main.cpp ${HEADER_FILES})

