cmake_minimum_required(VERSION 3.10)
project(seq)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(seq
        CMakeLists.txt
        Dictonary.cpp
        Dictonary.h
        main.cpp)
