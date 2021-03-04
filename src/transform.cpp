#include "transform.hpp"

Matrix cartesian_to_homogeneous(Vector3f vector)
{
    Matrix matrix{4, 1};
    matrix[0][0] = vector.x;
    matrix[1][0] = vector.y;
    matrix[2][0] = vector.z;
    matrix[3][0] = 1.0f;
    return matrix;
}

Vector3f homogeneous_to_cartesian(Matrix matrix)
{
    return Vector3f{matrix[0][0] / matrix[3][0], matrix[1][0] / matrix[3][0], matrix[2][0] / matrix[3][0]};
}

Matrix viewport(int x, int y, int width, int heigth, int depth)
{
    Matrix matrix = identity(4);
    
    matrix[0][0] = static_cast<float>(width / 2.0f);
    matrix[1][1] = static_cast<float>(heigth / 2.0f);
    matrix[2][2] = static_cast<float>(depth / 2.0f);

    matrix[0][3] = static_cast<float>(x + width / 2.0f);
    matrix[1][3] = static_cast<float>(y + heigth / 2.0f);
    matrix[2][3] = static_cast<float>(depth / 2.0f);

    return matrix;
}

Matrix projection(float eye)
{
    Matrix projection_matrix = identity(4);
    projection_matrix[3][2] = -1.0f / eye;
    return projection_matrix;
}

Matrix look_at(const Vector3f& eye, const Vector3f& center, const Vector3f& view_up)
{
    // Right hand coordinate system
    const auto w = unit_vector(eye - center); // look from eye to center
    const auto u = unit_vector(cross(view_up, w));
    const auto v = cross(w, u);
    
    // Camera_rotation^-1 * Camera_transle^-1
    return Matrix{{ {u.x, u.y, u.z, float(-dot(u, eye))},
                    {v.x, v.y, v.z, float(-dot(v, eye))},
                    {w.x, w.y, w.z, float(-dot(w, eye))},
                    {0, 0, 0, 1} }};
}