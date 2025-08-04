
add_executable(matrix_tests
    matrix_tests.cpp
)

target_include_directories(matrix_tests PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/../matrix_operations/include
)

target_link_libraries(matrix_tests PUBLIC matrix_lib)
