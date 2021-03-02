#include "scenes.hpp"
#include "matrix.hpp"
#include "model.hpp"
#include "rendering.hpp"
#include "tgaimage.h"
#include "transform.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <vector>

Vector3i world_to_screen(Vector3f pos, int width, int height)
{
    return Vector3i{int((pos.x + 1.0f) * width / 2.0f), int((pos.y + 1.0f) * height / 2.0f), int((pos.z + 1.0) * 255 / 2.0f)};
}

void draw_wire_mesh(const std::string& filename)
{
    const Model model{filename};
    const int width = 600;
    const int height = 600;
    TGAImage image{width, height, TGAImage::RGB};
    const TGAColor white{255, 255, 255, 255};
    const TGAColor red{255, 0, 0, 255};
    
    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        for (int j = 0; j < 3; ++j)
        {
            // Draw the triangle corresponding to the current face
            Vector3f start{model.vertex(face[j])};
            Vector3f end{model.vertex(face[(j + 1) % 3])};

            int x0 = static_cast<int>((start.x + 1.0f) * width / 2.0f);
            int y0 = static_cast<int>((start.y + 1.0f) * height / 2.0f);
            int x1 = static_cast<int>((end.x + 1.0f) * width / 2.0f);
            int y1 = static_cast<int>((end.y + 1.0f) * height / 2.0f);

            draw_line(Vector2i{x0, y0}, Vector2i{x1, y1}, image, white);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("1.wire_mesh.tga");
}

void draw_random_colored_triangles(const std::string& filename)
{
    const Model model{filename};
    const int width = 600;
    const int height = 600;
    TGAImage image{width, height, TGAImage::RGB};
    
    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector2i, 3> screen_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            Vector3f world_coordinates{model.vertex(face[j])};
            screen_coordinates[j] = Vector2i{static_cast<int>((world_coordinates.x + 1.0f) * width / 2.0f), 
                                             static_cast<int>((world_coordinates.y + 1.0f) * height / 2.0f)};
        }

        bounding_box_fill_triangle(screen_coordinates[0], screen_coordinates[1], screen_coordinates[2], image, TGAColor{random_uchar(), random_uchar(), random_uchar(), 255});
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("2.colored_filled_triangle.tga");
}

void draw_back_face_culling(const std::string& filename)
{
    const Model model{filename};
    const int width = 600;
    const int height = 600;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};

    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector3f, 3> world_coordinates;
        std::array<Vector2i, 3> screen_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            Vector3f vertex{model.vertex(face[j])};
            world_coordinates[j] = vertex;
            screen_coordinates[j] = Vector2i{static_cast<int>((vertex.x + 1.0f) * width / 2.0f), 
                                             static_cast<int>((vertex.y + 1.0f) * height / 2.0f)};
        }

        Vector3f normal = cross(world_coordinates[2] - world_coordinates[0], world_coordinates[1] - world_coordinates[0]);
        normal.normalize();
        double intensity = dot(normal, light_direction);
        
        if (intensity > 0)
        {
            auto color = static_cast<unsigned char>(intensity * 255);
            bounding_box_fill_triangle(screen_coordinates[0], screen_coordinates[1], screen_coordinates[2],
                                       image, TGAColor{color, color, color, 255});
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("3.back_face_culling.tga");
}

void draw_depth_buffer(const std::string& filename)
{
    const Model model{filename};
    const int width = 600;
    const int height = 600;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());

    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector3f, 3> world_coordinates;
        std::array<Vector3i, 3> screen_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            world_coordinates[j] = model.vertex(face[j]);
            screen_coordinates[j] = world_to_screen(world_coordinates[j], width, height);
        }

        Vector3f normal = cross(world_coordinates[2] - world_coordinates[0], world_coordinates[1] - world_coordinates[0]);
        normal.normalize();
        double intensity = dot(normal, light_direction);
        
        if (intensity > 0)
        {
            auto color = static_cast<unsigned char>(intensity * 255);
            bounding_box_fill_triangle(screen_coordinates[0], screen_coordinates[1], screen_coordinates[2],
                                        depth_buffer, image, TGAColor{color, color, color, 255});
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("4.depth_buffer.tga");
}

void draw_textured_depth_buffer(const std::string& filename)
{
    Model model{filename};
    const int width = 600;
    const int height = 600;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());

    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector3f, 3> world_coordinates;
        std::array<Vector3i, 3> screen_coordinates;
        std::array<Vector2f, 3> uv_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            world_coordinates[j] = model.vertex(face[j]);
            screen_coordinates[j] = world_to_screen(world_coordinates[j], width, height);
            uv_coordinates[j] = model.uv(i, j);
        }

        Vector3f normal = cross(world_coordinates[2] - world_coordinates[0], world_coordinates[1] - world_coordinates[0]);
        normal.normalize();
        double intensity = dot(normal, light_direction);
        
        if (intensity > 0)
        {
            auto color = static_cast<unsigned char>(intensity * 255);
            bounding_box_fill_triangle(screen_coordinates, uv_coordinates, model, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("5.texture_depth_buffer.tga");   
}

void draw_perspective_projection(const std::string& filename)
{
    Model model{filename};
    const int width = 600;
    const int height = 600;
    const int depth = 255;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    const Vector3f camera{0, 0, 3};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());
    
    Matrix projection_matrix = projection(camera.z);
    //std::cout << "Projection matrix:\n" << projection_matrix << "\n";
    const auto viewport_matrix = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    //std::cout << "Viewport matrix:\n" << viewport_matrix << "\n";
    const auto projection_transform = viewport_matrix * projection_matrix;
    //std::cout << "Projection transform:\n" << projection_transform << "\n";
    
    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector3f, 3> world_coordinates;
        std::array<Vector3i, 3> screen_coordinates;
        std::array<Vector2f, 3> uv_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            world_coordinates[j] = model.vertex(face[j]);
            screen_coordinates[j] = cast<int>(homogeneous_to_cartesian(projection_transform * cartesian_to_homogeneous(world_coordinates[j]))); 
            uv_coordinates[j] = model.uv(i, j);
        }

        Vector3f normal = cross(world_coordinates[2] - world_coordinates[0], world_coordinates[1] - world_coordinates[0]);
        normal.normalize();
        double intensity = dot(normal, light_direction);
        
        if (intensity > 0)
        {
            auto color = static_cast<unsigned char>(intensity * 255);
            bounding_box_fill_triangle(screen_coordinates, uv_coordinates, model, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("6.projective_perspective.tga"); 
}

void draw_gouraud_shading(const std::string& filename)
{
    Model model{filename};
    const int width = 600;
    const int height = 600;
    const int depth = 255;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    const Vector3f camera{0, 0, 3};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());
    
    Matrix projection_matrix = projection(camera.z);
    //std::cout << "Projection matrix:\n" << projection_matrix << "\n";
    const auto viewport_matrix = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    //std::cout << "Viewport matrix:\n" << viewport_matrix << "\n";
    const auto projection_transform = viewport_matrix * projection_matrix;
    //std::cout << "Projection transform:\n" << projection_transform << "\n";
    
    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector3f, 3> world_coordinates;
        std::array<Vector3i, 3> screen_coordinates;
        std::array<float, 3> intensities;
        for (int j = 0; j < 3; ++j)
        {
            world_coordinates[j] = model.vertex(face[j]);
            screen_coordinates[j] = cast<int>(homogeneous_to_cartesian(projection_transform * cartesian_to_homogeneous(world_coordinates[j])));
            intensities[j] = float(dot(model.normal(i, j), light_direction));
        }

        Vector3f normal = cross(world_coordinates[2] - world_coordinates[0], world_coordinates[1] - world_coordinates[0]);
        normal.normalize();
        double intensity = dot(normal, light_direction);
        
        if (intensity > 0)
        {
            auto color = static_cast<unsigned char>(intensity * 255);
            fill_triangle_gouraud(screen_coordinates, intensities, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("7.perspective_gouraud_shading.tga"); 
}