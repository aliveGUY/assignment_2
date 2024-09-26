cmake_minimum_required(VERSION 3.0)

project(test)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(test main.cpp)

target_link_libraries(test ${MPI_LIBRARIES})
