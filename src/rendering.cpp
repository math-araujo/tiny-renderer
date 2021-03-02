#include "rendering.hpp"
#include "model.hpp"
#include "rendering.hpp"
#include "util.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

void draw_line(Vector2i start, Vector2i end, TGAImage& image, TGAColor color)
{
    bool steep = false;
    /*If the height is greater than the width, it's necessary to
    rewrite the loop such as x = ay + b instead of y = ax + b.
    Instead of duplicating the code, it's easier to simple swap
    x and y values.
    */
    if (std::abs(end.x - start.x) < std::abs(end.y - start.y))
    {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
        steep = true;
    }

    if (start.x > end.x) // Ensure that the line is draw left to right
    {
        std::swap(start, end);
    }

    /*
    Derivation for the formulas and algorithm:
    https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Derivation
    
    Janke - Mathematical Structures for Computer Graphics, Chapter 10, Section 1.
    */
    
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    const int increment = 2 * std::abs(dy);
    int cumulative_error = 0;
    int y = start.y;
    for (int x = start.x; x <= end.x; ++x)
    {
        if (steep) // higher than wider
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }

        cumulative_error += increment;
        
        if (cumulative_error > dx)
        {
            y += (end.y > start.y ? 1 : -1);
            cumulative_error -= 2 * dx;
        }
    }
}

void line_sweeping_fill_triangle(Vector2i vertex0, Vector2i vertex1, Vector2i vertex2, TGAImage& image, const TGAColor& color)
{
    if (vertex0.y == vertex1.y && vertex0.y == vertex2.y) // Degenerate triangle: three collinear points
    {
        return;
    }

    // Sort vertices according the y-coordinates such that vertex0.y <= vertex1.y <= vertex2.y
    if (vertex0.y > vertex1.y)
    {
        std::swap(vertex0, vertex1);
    }

    if (vertex0.y > vertex2.y)
    {
        std::swap(vertex0, vertex2);
    }

    if (vertex1.y > vertex2.y)
    {
        std::swap(vertex1, vertex2);
    }

    /*
    For each y in range between vertex0.y and vertex2.y, draw a horizontal line
    connecting the left and right sides of the triangle
    */
    const int max_vertical_distance = vertex2.y - vertex0.y;
    for (int i = 0; i < max_vertical_distance; ++i)
    {
        const bool upper_triangle = i > vertex1.y - vertex0.y || vertex1.y == vertex0.y;
        const int partial_vertical_distance = upper_triangle ? vertex2.y - vertex1.y : vertex1.y - vertex0.y;
        
        /*
        A point P between V0 and V1 can be written as
        P = (1 - t) * V0 + t* V1 = V0 + t * (V1 - V0), for 0 <= t <= 1
        
        alpha and beta allows to compute points on the edges of the
        triangle in function of the endpoints of the edges. Then it's
        possible to draw a horizontal line connecting the left and right
        points.
        alpha is the parameter of the point on the "larger" edge, with
        endpoints on vertex0 and vertex2.
        beta is the parameter of the other two edges, and it's computation
        changes depending if the iteration is on the bottom triangle (with
        endpoints v0 and v1) or upper triangle (with endpoints v1 and v2).
        */

        float alpha = static_cast<float>(i) / max_vertical_distance;
        int vertical_correction = upper_triangle ? vertex1.y - vertex0.y : 0;
        float beta = static_cast<float>(i - vertical_correction) / partial_vertical_distance;
        
        Vector2i left_endpoint{vertex0 + alpha * (vertex2 - vertex0)};
        Vector2i right_endpoint{upper_triangle ? vertex1 + beta * (vertex2 - vertex1) : vertex0 + beta * (vertex1 - vertex0)};

        if (left_endpoint.x > right_endpoint.x)
        {
            std::swap(left_endpoint, right_endpoint);
        }

        for (int j = left_endpoint.x; j <= right_endpoint.x; ++j)
        {
            image.set(j, vertex0.y + i, color);
        }
    }
}

void bounding_box_fill_triangle(Vector2i vertex0, Vector2i vertex1, Vector2i vertex2, TGAImage& image, const TGAColor& color)
{
    Vector2i min_bounding_box{image.get_width() - 1, image.get_height() - 1};
    Vector2i max_bounding_box{0, 0};
    Vector2i clamp{image.get_width() - 1, image.get_height() - 1};
    const std::array<Vector2i, 3> vertices{vertex0, vertex1, vertex2};

    for (int i = 0; i < vertices.size(); ++i)
    {
        min_bounding_box.x = std::max(0, std::min(min_bounding_box.x, vertices[i].x));
        min_bounding_box.y = std::max(0, std::min(min_bounding_box.y, vertices[i].y));

        max_bounding_box.x = std::min(clamp.x, std::max(max_bounding_box.x, vertices[i].x));
        max_bounding_box.y = std::min(clamp.y, std::max(max_bounding_box.y, vertices[i].y));
    }

    Vector2i draw_point;
    for (draw_point.x = min_bounding_box.x; draw_point.x <= max_bounding_box.x; ++draw_point.x)
    {
        for (draw_point.y = min_bounding_box.y; draw_point.y <= max_bounding_box.y; ++draw_point.y)
        {
            if (is_inside_triangle(vertices, draw_point))
            {
                image.set(draw_point.x, draw_point.y, color);
            }
        }
    }
}

void bounding_box_fill_triangle(Vector3i vertex0, Vector3i vertex1, Vector3i vertex2, std::vector<float>& depth_buffer, TGAImage& image, const TGAColor& color)
{
    Vector2i min_bounding_box{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    Vector2i max_bounding_box{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
    Vector2i clamp{image.get_width() - 1, image.get_height() - 1};
    const std::array<Vector3i, 3> vertices{vertex0, vertex1, vertex2};
    
    for (int i = 0; i < vertices.size(); ++i)
    {
        min_bounding_box.x = std::max(0, std::min(min_bounding_box.x, vertices[i].x));
        min_bounding_box.y = std::max(0, std::min(min_bounding_box.y, vertices[i].y));

        max_bounding_box.x = std::min(clamp.x, std::max(max_bounding_box.x, vertices[i].x));
        max_bounding_box.y = std::min(clamp.y, std::max(max_bounding_box.y, vertices[i].y));
    }
    
    Vector3i draw_point;
    
    for (draw_point.x = min_bounding_box.x; draw_point.x <= max_bounding_box.x; ++draw_point.x)
    {
        for (draw_point.y = min_bounding_box.y; draw_point.y <= max_bounding_box.y; ++draw_point.y)
        {
            const auto barycentric = barycentric_coordinates(vertices, draw_point);
            
            if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
            {
                continue;
            }

            auto z_coord = float(dot(barycentric, cast<float>(Vector3i{vertex0.z, vertex1.z, vertex2.z})));

            const int index = static_cast<int>(draw_point.x + draw_point.y * image.get_width());
            
            if (depth_buffer[index] < z_coord)
            {
                depth_buffer[index] = z_coord;
                image.set(draw_point.x, draw_point.y, color);
            }
        }
    }
}

void bounding_box_fill_triangle(const std::array<Vector3i, 3>& vertices, const std::array<Vector2f, 3>& uv_coordinates, Model& model, std::vector<float>& depth_buffer, TGAImage& image)
{
    Vector2i min_bounding_box{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    Vector2i max_bounding_box{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
    Vector2i clamp{image.get_width() - 1, image.get_height() - 1};
    
    for (int i = 0; i < vertices.size(); ++i)
    {
        min_bounding_box.x = std::max(0, std::min(min_bounding_box.x, vertices[i].x));
        min_bounding_box.y = std::max(0, std::min(min_bounding_box.y, vertices[i].y));

        max_bounding_box.x = std::min(clamp.x, std::max(max_bounding_box.x, vertices[i].x));
        max_bounding_box.y = std::min(clamp.y, std::max(max_bounding_box.y, vertices[i].y));
    }

    Vector3i draw_point;
    for (draw_point.x = min_bounding_box.x; draw_point.x <= max_bounding_box.x; ++draw_point.x)
    {
        for (draw_point.y = min_bounding_box.y; draw_point.y <= max_bounding_box.y; ++draw_point.y)
        {
            const auto barycentric = barycentric_coordinates(vertices, draw_point);
            
            if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
            {
                continue;
            }

            auto z_coord = float(dot(barycentric, cast<float>(Vector3i{vertices[0].z, vertices[1].z, vertices[2].z})));

            const int index = static_cast<int>(draw_point.x + draw_point.y * image.get_width());
            
            if (depth_buffer[index] < z_coord)
            {
                // texture.x = textures[0].x * bc.x + textures[1].x * bc.y + textures[2].x * bc.z;
                // texture.y = textures[0].y * bc.x + textures[0].y * bc.y + textures[2].y * bc.z;
                const auto texture_u = dot(Vector3{uv_coordinates[0].x, uv_coordinates[1].x, uv_coordinates[2].x}, barycentric);
                const auto texture_v = dot(Vector3{uv_coordinates[0].y, uv_coordinates[1].y, uv_coordinates[2].y}, barycentric);
                const Vector2f texture{static_cast<float>(texture_u), static_cast<float>(texture_v)};
                TGAColor color = model.diffuse_map_at(texture);
                depth_buffer[index] = z_coord;
                image.set(draw_point.x, draw_point.y, color);
            }
        }
    }
}

void fill_triangle_gouraud(const std::array<Vector3i, 3>& vertices, const std::array<float, 3>& intensities, std::vector<float>& depth_buffer, TGAImage& image)
{
    Vector2i min_bounding_box{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    Vector2i max_bounding_box{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
    Vector2i clamp{image.get_width() - 1, image.get_height() - 1};
    
    for (int i = 0; i < vertices.size(); ++i)
    {
        min_bounding_box.x = std::max(0, std::min(min_bounding_box.x, vertices[i].x));
        min_bounding_box.y = std::max(0, std::min(min_bounding_box.y, vertices[i].y));

        max_bounding_box.x = std::min(clamp.x, std::max(max_bounding_box.x, vertices[i].x));
        max_bounding_box.y = std::min(clamp.y, std::max(max_bounding_box.y, vertices[i].y));
    }

    Vector3i draw_point;
    for (draw_point.x = min_bounding_box.x; draw_point.x <= max_bounding_box.x; ++draw_point.x)
    {
        for (draw_point.y = min_bounding_box.y; draw_point.y <= max_bounding_box.y; ++draw_point.y)
        {
            const auto barycentric = barycentric_coordinates(vertices, draw_point);
            
            if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
            {
                continue;
            }

            auto z_coord = float(dot(barycentric, cast<float>(Vector3i{vertices[0].z, vertices[1].z, vertices[2].z})));

            const int index = static_cast<int>(draw_point.x + draw_point.y * image.get_width());
            
            if (depth_buffer[index] < z_coord)
            {
                const auto intensity = float(dot(Vector3{intensities[0], intensities[1], intensities[2]}, barycentric));
                const auto color = static_cast<unsigned char>(255 * intensity);
                depth_buffer[index] = z_coord;
                image.set(draw_point.x, draw_point.y, TGAColor{color, color, color, 255});
            }
        }
    }
}

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