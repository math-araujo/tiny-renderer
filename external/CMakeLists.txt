cmake_minimum_required(VERSION 3.12)
project(TGAImage)

add_library(tgaimage STATIC tgaimage.h tgaimage.cpp)
target_include_directories(tgaimage PUBLIC .)