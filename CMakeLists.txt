cmake_minimum_required(VERSION 3.12)
project(tiny-renderer)

add_subdirectory(external)

add_executable(main
    src/main.cpp
    src/scenes.hpp src/scenes.cpp
    src/rendering.hpp src/rendering.cpp
    src/matrix.hpp src/matrix.cpp
    src/vector.hpp
    src/model.hpp src/model.cpp
    src/util.hpp
    )
    
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE tgaimage)
