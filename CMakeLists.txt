cmake_minimum_required(VERSION 3.20)

project(matrix LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(matrix_operations)
add_subdirectory(app)
add_subdirectory(test_matrices)
