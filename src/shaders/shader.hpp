#ifndef SHADER_HPP
#define SHADER_HPP

#include "vector.hpp"

struct TGAColor;

struct Shader
{
    virtual ~Shader();
    virtual Vector3f vertex(int face, int vertex_number) = 0;
    virtual bool fragment(Vector3f barycentric_coordinates, TGAColor& color) = 0;
};

#endif // SHADER_HPP