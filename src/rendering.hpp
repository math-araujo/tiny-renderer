#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "geometry.hpp"
#include "tgaimage.h"
#include <array>

// Draw a line between start and end using the provided color
void draw_line(Vector2i start, Vector2i end, TGAImage& image, TGAColor color);

// Draw a triangle using the Line Sweeping algorithm using the provided color
void line_sweeping_fill_triangle(Vector2i vertex0, Vector2i vertex1, Vector2i vertex2, TGAImage& image, const TGAColor& color);

// Draw a triangle using the Bounding Box algorithm using the provided color
void bounding_box_fill_triangle(Vector2i vertex0, Vector2i vertex1, Vector2i vertex2, TGAImage& image, const TGAColor& color);

// Compute the barycentric coordinates of a point with respect to the triangle
Vector3f barycentric_coordinates(const std::array<Vector2i, 3>& vertices, Vector2i point);

/*
Original version of barycentric coordinates as found on the code of the book/wiki.
The cross product is done as cross((AC.x, AB.x, PA.x), (AC.y, AB.y, PA.y))
on the code, while the text uses cross((AB.x, AC.x, PA.x), (AB.y, AC.y, PA.y))
This changes requires that the barycentric coordinates are expressed as (1 - u - v, v, u),
instead of (1 - u - v, u, v), which is the formula given on the text.
*/
Vector3f tiny_barycentric_coordinates(const std::array<Vector2i, 3>& vertices, Vector2i point);

// Test function to compare barycentric_coordinates and tiny_barycentric_coordinates
void debug_compare_barycentric_coordinates();

// Test if the provided point is inside the triangle
bool is_inside_triangle(const std::array<Vector2i, 3>& vertices, Vector2i point);

#endif // RENDERING_HPP