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
void bounding_box_fill_triangle(Vector3f vertex0, Vector3f vertex1, Vector3f vertex2, std::vector<float>& depth_buffer, TGAImage& image, const TGAColor& color);

// Draw a filled triangle using the Bounding Box algorithm and depth buffering using an image texture
void bounding_box_fill_triangle(const std::array<Vector3f, 3>& vertices, const std::array<Vector2f, 3>& uv_coordinates, Model& model, std::vector<float>& depth_buffer, TGAImage& image);

// Compute the barycentric coordinates of a point with respect to the triangle specified by the vertices
template<typename T>
Vector3f barycentric_coordinates(const std::array<Vector2<T>, 3>& vertices, Vector2<T> point)
{
    Vector3f normal = cross(Vector3f{static_cast<float>(vertices[1].x - vertices[0].x),
                                     static_cast<float>(vertices[2].x - vertices[0].x),
                                     static_cast<float>(vertices[0].x - point.x)},
                            Vector3f{static_cast<float>(vertices[1].y - vertices[0].y),
                                     static_cast<float>(vertices[2].y - vertices[0].y),
                                     static_cast<float>(vertices[0].y - point.y)});
                                     
    if (std::abs(normal.z) < 1.0f)
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    normal *= 1 / normal.z;
    return Vector3f{1.0f - static_cast<float>(normal.x + normal.y), static_cast<float>(normal.x), static_cast<float>(normal.y)};
}

// Compute the barycentric coordinates of a point with respect to a triangle whose vertices are A, B, C
template<typename T>
Vector3f barycentric_coordinates(Vector2<T> A, Vector2f B, Vector2f C, Vector3f point)
{
    Vector3f normal = cross(Vector3f{static_cast<float>(B.x - A.x),
                                     static_cast<float>(C.x - A.x),
                                     static_cast<float>(A.x - point.x)},
                            Vector3f{static_cast<float>(B.y - A.y),
                                     static_cast<float>(C.y - A.y),
                                     static_cast<float>(A.y - point.y)});
                                     
    if (std::abs(normal.z) < 1.0f)
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    normal *= 1 / normal.z;
    return Vector3f{1.0f - static_cast<float>(normal.x + normal.y), static_cast<float>(normal.x), static_cast<float>(normal.y)};
}

// Compute the barycentric coordinates of a point with respect to the triangle specified by the vertices
template<typename T>
Vector3f barycentric_coordinates(const std::array<Vector3<T>, 3>& vertices, Vector3<T> point)
{
    Vector3f normal = cross(Vector3f{static_cast<float>(vertices[1].x - vertices[0].x),
                                     static_cast<float>(vertices[2].x - vertices[0].x),
                                     static_cast<float>(vertices[0].x - point.x)},
                            Vector3f{static_cast<float>(vertices[1].y - vertices[0].y),
                                     static_cast<float>(vertices[2].y - vertices[0].y),
                                     static_cast<float>(vertices[0].y - point.y)});
                                     
    if (std::abs(normal.z) < 1.0f)
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    normal *= 1 / normal.z;
    return Vector3f{1.0f - static_cast<float>(normal.x + normal.y), static_cast<float>(normal.x), static_cast<float>(normal.y)};
}

// Compute the barycentric coordinates of a point with respect to a triangle whose vertices are A, B, C
template<typename T>
Vector3f barycentric_coordinates(Vector3<T> A, Vector3f B, Vector3f C, Vector3f point)
{
    Vector3f normal = cross(Vector3f{static_cast<float>(B.x - A.x),
                                     static_cast<float>(C.x - A.x),
                                     static_cast<float>(A.x - point.x)},
                            Vector3f{static_cast<float>(B.y - A.y),
                                     static_cast<float>(C.y - A.y),
                                     static_cast<float>(A.y - point.y)});
                                     
    if (std::abs(normal.z) < 1.0f)
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    normal *= 1 / normal.z;
    return Vector3f{1.0f - static_cast<float>(normal.x + normal.y), static_cast<float>(normal.x), static_cast<float>(normal.y)};
}

/*
Original version of barycentric coordinates as found on the code of the book/wiki.
The cross product is done as cross((AC.x, AB.x, PA.x), (AC.y, AB.y, PA.y))
on the code, while the text uses cross((AB.x, AC.x, PA.x), (AB.y, AC.y, PA.y))
This changes requires that the barycentric coordinates are expressed as (1 - u - v, v, u),
instead of (1 - u - v, u, v), which is the formula given on the text.
*/
template<typename T>
Vector3f tiny_barycentric_coordinates(const std::array<Vector2<T>, 3>& vertices, Vector2<T> point)
{
    Vector3f normal = cross(Vector3f{static_cast<float>(vertices[2].x - vertices[0].x), static_cast<float>(vertices[1].x - vertices[0].x), static_cast<float>(vertices[0].x - point.x)}, Vector3f{static_cast<float>(vertices[2].y - vertices[0].y), static_cast<float>(vertices[1].y - vertices[0].y), static_cast<float>(vertices[0].y - point.y)});
    if (std::abs(normal.z) < 1) { return Vector3f{-1, 1, 1}; }
    return Vector3f{1.0f - (normal.x+normal.y)/normal.z, normal.y/normal.z, normal.x/normal.z};
}

template<typename T>
Vector3f tiny_barycentric_coordinates(const std::array<Vector3<T>, 3>& vertices, Vector3<T> point)
{
    Vector3f normal = cross(Vector3f{static_cast<float>(vertices[2].x - vertices[0].x), static_cast<float>(vertices[1].x - vertices[0].x), static_cast<float>(vertices[0].x - point.x)}, Vector3f{static_cast<float>(vertices[2].y - vertices[0].y), static_cast<float>(vertices[1].y - vertices[0].y), static_cast<float>(vertices[0].y - point.y)});
    if (std::abs(normal.z) < 1) { return Vector3f{-1, 1, 1}; }
    return Vector3f{1.0f - (normal.x+normal.y)/normal.z, normal.y/normal.z, normal.x/normal.z};
}


// Test function to compare barycentric_coordinates and tiny_barycentric_coordinates
void debug_compare_barycentric_coordinates();

// Test if the provided point is inside the triangle
bool is_inside_triangle(const std::array<Vector2i, 3>& vertices, Vector2i point);

#endif // RENDERING_HPP