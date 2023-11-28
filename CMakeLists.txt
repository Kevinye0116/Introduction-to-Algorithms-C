cmake_minimum_required(VERSION 3.26)
project(Introduction-to-Algorithms-C C)

set(CMAKE_C_STANDARD 17)

add_subdirectory(Part1-Foundations)
add_subdirectory(Part2-Sorting-and-Order-Statistics)
add_subdirectory(Part3-Data-Structures)


add_executable(test test.c)