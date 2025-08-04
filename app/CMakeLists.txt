add_executable(wayland_secondProject  main.cpp)
target_link_libraries(wayland_secondProject PRIVATE matrix_lib)
target_include_directories(wayland_secondProject PRIVATE 
    ${CMAKE_SOURCE_DIR}/matrix_operations/include
) 
