cmake_minimum_required(VERSION 3.12)
project(Shaders)

add_library(shaders STATIC 
    shader.hpp shader.cpp 
    gouraudshader.hpp gouraudshader.cpp 
    basictextureshader.hpp basictextureshader.cpp
    textureshader.hpp textureshader.cpp
    phongshader.hpp phongshader.cpp)
target_link_libraries(shaders PRIVATE tgaimage math geometry)
target_include_directories(shaders PUBLIC .)