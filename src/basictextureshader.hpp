#ifndef BASIC_TEXTURE_HPP
#define BASIC_TEXTURE_HPP

#include "matrix.hpp"
#include "shader.hpp"
#include <array>

class Model;

struct BasicTexture: Shader
{
    const Model& model;
    Matrix uniform_mvp; // Projection * ModelView
    Matrix uniform_mvpit; // Inverse of transpose of Projection * ModelView
    Matrix uniform_viewport;
    Matrix scene_transform; // Viewport * Projection * ModelView
    Vector3f light_direction;
    
    Vector3f varying_intensity; // written by vertex shader, read by fragment shader
    std::array<Vector2f, 3> varying_uv;
    std::array<Vector3f, 3> varying_normal;
    std::array<Matrix, 3> varying_triangle_coordinates;
    std::array<Vector3f, 3> varying_ndc;

    BasicTexture(const Model& object, const Matrix& model_view_transform, 
                 const Matrix& viewport_transform, const Vector3f& light_dir);

    Vector3f vertex(int face, int vertex_number) override;
    bool fragment(Vector3f barycentric_coordinates, TGAColor& color) override;
};

#endif // BASIC_TEXTURE_HPP