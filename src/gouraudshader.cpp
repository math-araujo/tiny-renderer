#include "gouraudshader.hpp"

#include "matrix.hpp"
#include "model.hpp"
#include "transform.hpp"
#include <algorithm>

Gouraud::Gouraud(const Model& object, const Matrix& model_view_transform, const Matrix& viewport_transform, const Vector3f& light_dir):
    model{object}, uniform_mvp{model_view_transform}, uniform_mvpit{transpose(inverse_4x4(model_view_transform))}, 
    uniform_viewport{viewport_transform}, scene_transform{uniform_viewport * uniform_mvp}, light_direction{light_dir}
{}

Vector3f Gouraud::vertex(int face, int vertex_number)
{
    varying_intensity[vertex_number] = std::max(0.0f, float(dot(model.normal(face, vertex_number), light_direction)));
    const auto gl_vertex = scene_transform * cartesian_to_homogeneous(model.vertex(face, vertex_number));
    return homogeneous_to_cartesian(std::move(gl_vertex));
}

bool Gouraud::fragment(Vector3f barycentric_coordinates, TGAColor& color)
{
    float intensity = float(dot(varying_intensity, barycentric_coordinates));
    color = TGAColor{255, 255, 255} * intensity;
    return false;
}

