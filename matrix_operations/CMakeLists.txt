add_library(matrix_lib SHARED src/matrix.cpp)
target_include_directories(matrix_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)