#ifndef TEXTURE_SHADER_HPP
#define TEXTURE_SHADER_HPP

#include "shader.hpp"
#include <array>

class Matrix;
class Model;

struct Texture: Shader
{
    const Model& model;
    const Matrix& transform;
    Vector3f varying_intensity{}; // written by vertex shader, read by fragment shader
    std::array<Vector2f, 3> varying_uv;

    Texture(const Model& object, const Matrix& scene_transform);
    
    Vector3f vertex(const Vector3f& light_direction, int face, int vertex_number) override;
    bool fragment(Vector3f barycentric_coordinates, TGAColor& color) override;
};

#endif // TEXTURE_SHADER_HPP