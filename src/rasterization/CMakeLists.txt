cmake_minimum_required(VERSION 3.12)
project(Rasterization)

add_library(rasterization STATIC rendering.hpp rendering.cpp)
target_link_libraries(rasterization PRIVATE tgaimage math geometry shaders)
target_include_directories(rasterization PUBLIC .)