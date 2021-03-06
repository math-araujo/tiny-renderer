cmake_minimum_required(VERSION 3.12)
project(tiny-renderer)

add_subdirectory(external)

add_executable(main
    src/main.cpp
    src/scenes.hpp src/scenes.cpp
    src/shader.hpp src/shader.cpp
    src/gouraudshader.hpp src/gouraudshader.cpp
    src/textureshader.hpp src/textureshader.cpp
    src/geometry.hpp src/geometry.cpp
    src/rendering.hpp src/rendering.cpp
    src/transform.hpp src/transform.cpp
    src/matrix.hpp src/matrix.cpp
    src/vector.hpp
    src/model.hpp src/model.cpp
    src/util.hpp
    )
    
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE tgaimage)
