cmake_minimum_required(VERSION 3.10.0)
project(task1 VERSION 0.1.0 LANGUAGES C CXX)

set(HEADER_FILES group.cpp user.cpp user.h group.h)

add_executable(task1 main.cpp ${HEADER_FILES})

