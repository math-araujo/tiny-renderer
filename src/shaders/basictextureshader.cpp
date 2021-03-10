#include "basictextureshader.hpp"
#include "trianglemesh.hpp"
#include "transform.hpp"

BasicTexture::BasicTexture(const TriangleMesh& object, const Matrix& model_view_transform, const Matrix& viewport_transform, const Vector3f& light_dir):
    model{object}, uniform_mvp{model_view_transform}, uniform_mvpit{transpose(inverse_4x4(model_view_transform))}, 
    uniform_viewport{viewport_transform}, scene_transform{uniform_viewport * uniform_mvp}, light_direction{light_dir}
    {}

Vector3f BasicTexture::vertex(int face, int vertex_number)
{
    varying_uv[vertex_number] = model.uv(face, vertex_number);
    varying_intensity[vertex_number] = std::max(0.0f, float(dot(model.normal(face, vertex_number), light_direction)));
    const auto gl_vertex = scene_transform * cartesian_to_homogeneous(model.vertex(face, vertex_number));
    return homogeneous_to_cartesian(std::move(gl_vertex));
}

bool BasicTexture::fragment(Vector3f barycentric_coordinates, TGAColor& color)
{
    float intensity = float(dot(barycentric_coordinates, varying_intensity));
    Vector2f uv{float(dot(Vector3f{varying_uv[0].x, varying_uv[1].x, varying_uv[2].x}, barycentric_coordinates)),
                float(dot(Vector3f{varying_uv[0].y, varying_uv[1].y, varying_uv[2].y}, barycentric_coordinates))};
    
    color = model.diffuse_map_at(uv) * intensity;
    return false;    
}
