cmake_minimum_required(VERSION 3.10.0)
project(task2 VERSION 0.1.0 LANGUAGES C CXX)

set(HEADER_FILES typelist.h)

# add_compile_options(-fconcepts)

add_executable(homeworks main.cpp ${HEADER_FILES})

