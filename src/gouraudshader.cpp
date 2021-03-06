#include "gouraudshader.hpp"

#include "matrix.hpp"
#include "model.hpp"
#include "transform.hpp"
#include <algorithm>

Gouraud::Gouraud(const Model& object, const Matrix& scene_transform): model{object}, transform{scene_transform}
{}

Vector3f Gouraud::vertex(const Vector3f& light_direction, int face, int vertex_number)
{
    varying_intensity[vertex_number] = std::max(0.0f, float(dot(model.normal(face, vertex_number), light_direction)));
    const auto gl_vertex = transform * cartesian_to_homogeneous(model.vertex(face, vertex_number));
    return homogeneous_to_cartesian(std::move(gl_vertex));
}

bool Gouraud::fragment(Vector3f barycentric_coordinates, TGAColor& color)
{
    float intensity = float(dot(varying_intensity, barycentric_coordinates));
    color = TGAColor{255, 255, 255} * intensity;
    return false;
}

