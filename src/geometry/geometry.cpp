#include "geometry.hpp"
#include <iostream>

void debug_compare_barycentric_coordinates()
{
    std::array<Vector2i, 3> triangle0{Vector2i{3, 2}, Vector2i{5, 3}, Vector2i{2, 4}};
    std::cout << "My test: " << barycentric_coordinates(triangle0, Vector2i{4, 2}) << "\n";
    std::cout << "Tiny code: " << tiny_barycentric_coordinates(triangle0, Vector2i{4, 2}) << "\n";
}

bool is_inside_triangle(const std::array<Vector2i, 3>& vertices, Vector2i point)
{
    Vector3f barycentric = barycentric_coordinates(vertices, point);
    
    if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
    {
        return false;
    }

    return true;
}