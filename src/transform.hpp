#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

Matrix cartesian_to_homogeneous(Vector3f vector);
Vector3f homogeneous_to_cartesian(Matrix matrix);
Matrix viewport(int x, int y, int width, int heigth, int depth);
Matrix projection(float eye);
// Reference: http://www.songho.ca/opengl/gl_camera.html#lookat
Matrix look_at(const Vector3f& eye, const Vector3f& center, const Vector3f& view_up);

#endif // TRANSFORM_HPP