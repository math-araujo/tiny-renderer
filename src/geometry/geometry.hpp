#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "vector.hpp"
#include <array>
#include <limits>

// Compute the barycentric coordinates of a point with respect to the triangle specified by the vertices
template<typename T>
Vector3f barycentric_coordinates(const std::array<Vector2<T>, 3>& vertices, Vector2<T> point)
{
    auto normal = cross(Vector3<T>{vertices[1].x - vertices[0].x, vertices[2].x - vertices[0].x, vertices[0].x - point.x},
                        Vector3<T>{vertices[1].y - vertices[0].y, vertices[2].y - vertices[0].y, vertices[0].y - point.y});
                                     
    if (std::abs(static_cast<float>(normal.z)) <= std::numeric_limits<float>::epsilon())
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    auto normal_z = static_cast<float>(normal.z);
    return Vector3f{1 - (normal.x + normal.y) / normal_z, normal.x / normal_z, normal.y / normal_z };   
}

// Compute the barycentric coordinates of a point with respect to a triangle whose vertices are A, B, C
template<typename T>
Vector3f barycentric_coordinates(Vector2<T> A, Vector2f B, Vector2f C, Vector3f point)
{
    auto normal = cross(Vector3<T>{B.x - A.x, C.x - A.x, A.x - point.x},
                        Vector3<T>{B.y - A.y, C.y - A.y, A.y - point.y});
                                     
    if (std::abs(static_cast<float>(normal.z)) <= std::numeric_limits<float>::epsilon())
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    auto normal_z = static_cast<float>(normal.z);
    return Vector3f{1 - (normal.x + normal.y) / normal_z, normal.x / normal_z, normal.y / normal_z };
}

// Compute the barycentric coordinates of a point with respect to the triangle specified by the vertices
template<typename T>
Vector3f barycentric_coordinates(const std::array<Vector3<T>, 3>& vertices, Vector3<T> point)
{
    auto normal = cross(Vector3<T>{vertices[1].x - vertices[0].x, vertices[2].x - vertices[0].x, vertices[0].x - point.x},
                        Vector3<T>{vertices[1].y - vertices[0].y, vertices[2].y - vertices[0].y, vertices[0].y - point.y});                                   
                                     
    if (std::abs(static_cast<float>(normal.z)) <= std::numeric_limits<float>::epsilon())
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    auto normal_z = static_cast<float>(normal.z);
    return Vector3f{1 - (normal.x + normal.y) / normal_z, normal.x / normal_z, normal.y / normal_z };
}

// Compute the barycentric coordinates of a point with respect to a triangle whose vertices are A, B, C
template<typename T>
Vector3f barycentric_coordinates(Vector3<T> A, Vector3f B, Vector3f C, Vector3f point)
{
    auto normal = cross(Vector3<T>{B.x - A.x, C.x - A.x, A.x - point.x},
                        Vector3<T>{B.y - A.y, C.y - A.y, A.y - point.y});
                                     
    if (std::abs(static_cast<float>(normal.z)) <= std::numeric_limits<float>::epsilon())
    { 
        return Vector3f{-1.0f, 1.0f, 1.0f};
    }

    auto normal_z = static_cast<float>(normal.z);
    return Vector3f{1 - (normal.x + normal.y) / normal_z, normal.x / normal_z, normal.y / normal_z };
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

#endif // GEOMETRY_HPP