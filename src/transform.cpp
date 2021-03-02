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