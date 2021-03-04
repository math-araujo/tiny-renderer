#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "tgaimage.h"
#include "vector.hpp"
#include <array>
#include <vector>

class Model;

// Draw a line between start and end using the provided color
void draw_line(Vector2i start, Vector2i end, TGAImage& image, TGAColor color);

// Draw a filled triangle using the Line Sweeping algorithm using the provided color
void line_sweeping_fill_triangle(Vector2i vertex0, Vector2i vertex1, Vector2i vertex2, TGAImage& image, const TGAColor& color);

// Draw a filled triangle using the Bounding Box algorithm using the provided color
void bounding_box_fill_triangle(Vector2i vertex0, Vector2i vertex1, Vector2i vertex2, TGAImage& image, const TGAColor& color);

// Draw a filled triangle using the Bounding Box algorithm and depth buffering using the provided color
void bounding_box_fill_triangle(Vector3i vertex0, Vector3i vertex1, Vector3i vertex2, std::vector<float>& depth_buffer, TGAImage& image, const TGAColor& color);

// Draw a filled triangle using the Bounding Box algorithm and depth buffering using an image texture
void bounding_box_fill_triangle(const std::array<Vector3i, 3>& vertices, const std::array<Vector2f, 3>& uv_coordinates, Model& model, std::vector<float>& depth_buffer, TGAImage& image);

// Draw a filled triangle using the Bounding Box algorithm and depth buffering using an image texture
void bounding_box_fill_triangle(const std::array<Vector3i, 3>& vertices, const std::array<Vector2f, 3>& uv_coordinates, float light_intensity, Model& model, std::vector<float>& depth_buffer, TGAImage& image);

void fill_triangle_gouraud(const std::array<Vector3i, 3>& vertices, const std::array<float, 3>& intensities, std::vector<float>& depth_buffer, TGAImage& image);

#endif // RENDERING_HPP