cmake_minimum_required(VERSION 3.6)
project(seq)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FileReader.cpp RSA.cpp)
add_executable(seq ${SOURCE_FILES})