#include "textureshader.hpp"
#include "transform.hpp"
#include "trianglemesh.hpp"

Texture::Texture(const TriangleMesh& object, const Matrix& model_view_transform, const Matrix& viewport_transform, const Vector3f& light_dir):
    model{object}, uniform_mvp{model_view_transform}, uniform_mvpit{transpose(inverse_4x4(model_view_transform))}, uniform_viewport{viewport_transform},
    light_direction{unit_vector(homogeneous_to_cartesian(uniform_mvp * cartesian_to_homogeneous(light_dir, 0.0f)))}
    {}

Vector3f Texture::vertex(int face, int vertex_number)
{
    varying_uv[vertex_number] = model.uv(face, vertex_number);

    varying_intensity[vertex_number] = std::max(0.0f, float(dot(model.normal(face, vertex_number), light_direction)));
    
    // homogeneous_to_cartesian(uniform_mvpit * cartesian_to_homogeneous(model.normal(face, vertex_number), 0.0f)) doesn't work, why??
    varying_normal[vertex_number] = drop_homogeneous_coordinate(uniform_mvpit * cartesian_to_homogeneous(model.normal(face, vertex_number), 0.0f));

    const auto gl_vertex = uniform_mvp * cartesian_to_homogeneous(model.vertex(face, vertex_number));
    varying_triangle_coordinates[vertex_number] = gl_vertex;
    varying_ndc[vertex_number] = homogeneous_to_cartesian(gl_vertex);
    return homogeneous_to_cartesian(uniform_viewport * gl_vertex);
}

bool Texture::fragment(Vector3f barycentric_coordinates, TGAColor& color)
{
    Vector2f uv{float(dot(barycentric_coordinates, Vector3f{varying_uv[0].x, varying_uv[1].x, varying_uv[2].x})),
                float(dot(barycentric_coordinates, Vector3f{varying_uv[0].y, varying_uv[1].y, varying_uv[2].y}))};
    
    Vector3f normal = unit_vector(Vector3f
    {
        float(dot(barycentric_coordinates, Vector3f{varying_normal[0].x, varying_normal[1].x, varying_normal[2].x})),
        float(dot(barycentric_coordinates, Vector3f{varying_normal[0].y, varying_normal[1].y, varying_normal[2].y})),
        float(dot(barycentric_coordinates, Vector3f{varying_normal[0].z, varying_normal[1].z, varying_normal[2].z}))
    });

    Matrix A{3, 3};
    A.fill_row(0, varying_ndc[1] - varying_ndc[0]);
    A.fill_row(1, varying_ndc[2] - varying_ndc[0]);
    A.fill_row(2, normal);

    auto inverse_A = inverse_3x3(A);
    Vector3f i = inverse_A * Vector3f{varying_uv[1].x - varying_uv[0].x, varying_uv[2].x - varying_uv[0].x, 0.0f};
    Vector3f j = inverse_A * Vector3f{varying_uv[1].y - varying_uv[0].y, varying_uv[2].y - varying_uv[0].y, 0.0f};

    Matrix B{3, 3};
    B.fill_column(0, unit_vector(i));
    B.fill_column(1, unit_vector(j));
    B.fill_column(2, normal);

    Vector3f n = unit_vector(B * model.normal_map_at(uv));
    const float diff = std::max(0.0f, float(dot(n, light_direction)));
    color = model.diffuse_map_at(uv) * diff;
    
    return false;
}