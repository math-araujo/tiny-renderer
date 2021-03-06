#include "textureshader.hpp"
#include "matrix.hpp"
#include "model.hpp"
#include "transform.hpp"

Texture::Texture(const Model& object, const Matrix& scene_transform): model{object}, transform{scene_transform}
{}

Vector3f Texture::vertex(const Vector3f& light_direction, int face, int vertex_number)
{
    varying_uv[vertex_number] = model.uv(face, vertex_number);
    varying_intensity[vertex_number] = std::max(0.0f, float(dot(model.normal(face, vertex_number), light_direction)));
    const auto gl_vertex = transform * cartesian_to_homogeneous(model.vertex(face, vertex_number));
    return homogeneous_to_cartesian(std::move(gl_vertex));
}

bool Texture::fragment(Vector3f barycentric_coordinates, TGAColor& color)
{
    float intensity = float(dot(barycentric_coordinates, varying_intensity));
    Vector2f uv{float(dot(Vector3f{varying_uv[0].x, varying_uv[1].x, varying_uv[2].x}, barycentric_coordinates)),
                float(dot(Vector3f{varying_uv[0].y, varying_uv[1].y, varying_uv[2].y}, barycentric_coordinates))};
    
    color = model.diffuse_map_at(uv) * intensity;
    return false;
}