#ifndef GOURAUD_SHADER_HPP
#define GOURAUD_SHADER_HPP

#include "matrix.hpp"
#include "shader.hpp"
#include <array>

class TriangleMesh;

struct Gouraud: public Shader
{
    const TriangleMesh& model;
    Matrix uniform_mvp; // Projection * ModelView
    Matrix uniform_mvpit; // Inverse of transpose of Projection * ModelView
    Matrix uniform_viewport;
    Matrix scene_transform; // Viewport * Projection * ModelView
    Vector3f light_direction;
    
    Vector3f varying_intensity; // written by vertex shader, read by fragment shader

    Gouraud(const TriangleMesh& object, const Matrix& model_view_transform, 
            const Matrix& viewport_transform, const Vector3f& light_dir);
    Vector3f vertex(int face, int vertex_number) override;
    bool fragment(Vector3f barycentric_coordinates, TGAColor& color) override;
};

#endif // GOURAUD_SHADER_HPP