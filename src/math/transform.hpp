#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

Matrix cartesian_to_homogeneous(Vector3f vector, float w = 1.0f);
Matrix homogenize(Matrix matrix);
Vector3f homogeneous_to_cartesian(Matrix matrix);
Matrix viewport(int x, int y, int width, int heigth, int depth);
Matrix projection(float eye);

/*
Difference between gl_look_at and look_at: 
gl_look_at place the camera at the origin facing the -Z axis, look_at place the camera
at z-axis facing the origin.
Source: https://github.com/ssloy/tinyrenderer/issues/62
*/
Matrix look_at(const Vector3f& eye, const Vector3f& center, const Vector3f& view_up);

// Reference: http://www.songho.ca/opengl/gl_camera.html#lookat
Matrix gl_look_at(const Vector3f& eye, const Vector3f& center, const Vector3f& view_up);

#endif // TRANSFORM_HPP