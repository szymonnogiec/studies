cmake_minimum_required(VERSION 3.6)
project(mpi)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

set(SOURCE_FILES main.cpp FileReader.cpp RSA.cpp)
add_executable(mpi ${SOURCE_FILES})

target_link_libraries(mpi ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(mpi PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(mpi PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()