cmake_minimum_required(VERSION 3.12)
project(Geometry)

add_library(geometry STATIC geometry.hpp geometry.cpp trianglemesh.hpp trianglemesh.cpp)
target_link_libraries(geometry PRIVATE tgaimage math)
target_include_directories(geometry PUBLIC .)