#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

Matrix cartesian_to_homogeneous(Vector3f vector);
Vector3f homogeneous_to_cartesian(Matrix matrix);
Matrix viewport(int x, int y, int width, int heigth, int depth);

#endif // TRANSFORM_HPP