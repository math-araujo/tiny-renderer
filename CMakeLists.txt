cmake_minimum_required(VERSION 3.12)
project(tiny-renderer)

add_subdirectory(tgaimage)
add_subdirectory(src/math)
add_subdirectory(src/geometry)
add_subdirectory(src/shaders)
add_subdirectory(src/rasterization)

add_executable(main src/main.cpp src/scenes.hpp src/scenes.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE tgaimage math geometry shaders rasterization)
