cmake_minimum_required(VERSION 3.10)
project(mpi_prir)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})


include_directories(.)

add_executable(mpi_prir
        CMakeLists.txt
        Dictonary.h
        main.cpp)

target_link_libraries(mpi_prir ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(mpi_prir PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(mpi_prir PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()