#ifndef GOURAUD_SHADER_HPP
#define GOURAUD_SHADER_HPP

#include "shader.hpp"
#include "vector.hpp"

class Matrix;
class Model;

struct Gouraud: public Shader
{
    const Model& model;
    const Matrix& transform;
    Vector3f varying_intensity{}; // written by vertex shader, read by fragment shader

    Gouraud(const Model& object, const Matrix& scene_transform);
    Vector3f vertex(const Vector3f& light_direction, int face, int vertex_number) override;
    bool fragment(Vector3f barycentric_coordinates, TGAColor& color) override;
};

#endif // GOURAUD_SHADER_HPP