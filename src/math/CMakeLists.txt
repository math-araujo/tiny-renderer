cmake_minimum_required(VERSION 3.12)
project(Math)

add_library(math STATIC random.hpp vector.hpp matrix.hpp matrix.cpp transform.hpp transform.cpp)
target_include_directories(math PUBLIC .)