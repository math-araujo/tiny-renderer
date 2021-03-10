#include "basictextureshader.hpp"
#include "scenes.hpp"
#include "gouraudshader.hpp"
#include "matrix.hpp"
#include "phongshader.hpp"
#include "rendering.hpp"
#include "textureshader.hpp"
#include "tgaimage.h"
#include "transform.hpp"
#include "trianglemesh.hpp"
#include "random.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

Vector3i world_to_screen(Vector3f pos, int width, int height)
{
    return Vector3i{int((pos.x + 1.0f) * width / 2.0f), int((pos.y + 1.0f) * height / 2.0f), int((pos.z + 1.0) * 255 / 2.0f)};
}

void draw_wire_mesh(const std::string& filename)
{
    const TriangleMesh model{filename};
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
    const std::string output_file = "1." + parse_filename(filename) + "_wire_mesh.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_random_colored_triangles(const std::string& filename)
{
    const TriangleMesh model{filename};
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

        fill_colored_triangle(screen_coordinates[0], screen_coordinates[1], screen_coordinates[2], image, TGAColor{random_uchar(), random_uchar(), random_uchar(), 255});
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "2." + parse_filename(filename) + "_colored_filled_triangle.tga";
    image.write_tga_file(output_file.c_str());
}

void draw_back_face_culling(const std::string& filename)
{
    const TriangleMesh model{filename};
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
            fill_colored_triangle(screen_coordinates[0], screen_coordinates[1], screen_coordinates[2],
                                  image, TGAColor{color, color, color, 255});
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "3." + parse_filename(filename) + "_back_face_culling.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_depth_buffer(const std::string& filename)
{
    const TriangleMesh model{filename};
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
            fill_colored_triangle(screen_coordinates[0], screen_coordinates[1], screen_coordinates[2],
                                  depth_buffer, image, TGAColor{color, color, color, 255});
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "4." + parse_filename(filename) + "_depth_buffer.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_textured_depth_buffer(const std::string& filename)
{
    TriangleMesh model{filename};
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
            fill_textured_triangle(screen_coordinates, uv_coordinates, model, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "5." + parse_filename(filename) + "_texture_depth_buffer.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_perspective_projection(const std::string& filename)
{
    TriangleMesh model{filename};
    const int width = 600;
    const int height = 600;
    const int depth = 255;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    const Vector3f camera{0, 0, 3};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());
    
    Matrix projection_matrix = projection(camera.z);
    const auto viewport_matrix = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    const auto projection_transform = viewport_matrix * projection_matrix;
    
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
            fill_textured_triangle(screen_coordinates, uv_coordinates, model, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "6." + parse_filename(filename) + "_projective_perspective.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_gouraud_shading(const std::string& filename)
{
    const TriangleMesh model{filename};
    const int width = 600;
    const int height = 600;
    const int depth = 255;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    const Vector3f camera{0, 0, 3};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());
    
    const Matrix projection_matrix = projection(camera.z);
    const auto viewport_matrix = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    const auto projection_transform = viewport_matrix * projection_matrix;
    
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
            fill_triangle_gouraud(screen_coordinates, intensities, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "7." + parse_filename(filename) + "_perspective_gouraud_shading.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_look_at(const std::string& filename)
{
    const TriangleMesh model{filename};
    const int width = 600;
    const int height = 600;
    const int depth = 255;
    TGAImage image{width, height, TGAImage::RGB};
    const Vector3f light_direction{0, 0, -1};
    const Vector3f camera{1, 1, 3};
    const Vector3f center{0, 0, 0};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());
    
    const Matrix view_matrix = look_at(camera, center, Vector3f{0, 1, 0});
    const Matrix projection_matrix = projection(float((camera - center).length()));
    const auto viewport_matrix = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    const auto scene_transform = viewport_matrix * projection_matrix * view_matrix;
    
    for (int i = 0; i < model.number_faces(); ++i)
    {
        const auto& face = model.face(i);

        std::array<Vector3f, 3> world_coordinates;
        std::array<Vector3i, 3> screen_coordinates;
        std::array<Vector2f, 3> uv_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            world_coordinates[j] = model.vertex(face[j]);
            screen_coordinates[j] = cast<int>(homogeneous_to_cartesian(scene_transform * cartesian_to_homogeneous(world_coordinates[j]))); 
            uv_coordinates[j] = model.uv(i, j);
        }

        Vector3f normal = cross(world_coordinates[2] - world_coordinates[0], world_coordinates[1] - world_coordinates[0]);
        normal.normalize();
        float intensity = float(dot(normal, light_direction));
        
        if (intensity > 0)
        {
            fill_textured_triangle(screen_coordinates, uv_coordinates, intensity, model, depth_buffer, image);
        }
    }

    image.flip_vertically(); // set origin to left bottom corner
    const std::string output_file = "8." + parse_filename(filename) + "_look_at.tga";
    image.write_tga_file(output_file.c_str()); 
}

void draw_our_gl(const std::string& filename, ShadersOptions shader_choice)
{
    const TriangleMesh model{filename};
    const int width = 600;
    const int height = 600;
    const int depth = 255;
    TGAImage image{width, height, TGAImage::RGB};
    const auto light_direction = unit_vector(Vector3f{1, 1, 1});
    const Vector3f camera{1, 1, 3};
    const Vector3f center{0, 0, 0};
    std::vector<float> depth_buffer(width * height, std::numeric_limits<float>::lowest());
    
    const Matrix view_matrix = look_at(camera, center, Vector3f{0, 1, 0});
    const Matrix projection_matrix = projection(float((camera - center).length()));
    const auto viewport_matrix = viewport(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    const auto model_view_projection_transform = projection_matrix * view_matrix;
    const auto scene_transform = viewport_matrix * model_view_projection_transform;
    
    std::unique_ptr<Shader> shader;
    std::string output_file{"9." + parse_filename(filename) + "_our_gl"};
    if (shader_choice == ShadersOptions::Gouraud)
    {
        shader = std::make_unique<Gouraud>(model, model_view_projection_transform, viewport_matrix, light_direction);
        output_file += "_gouraud.tga";
    }
    else if (shader_choice == ShadersOptions::BasicTexture)
    {
        shader = std::make_unique<BasicTexture>(model, model_view_projection_transform, viewport_matrix, light_direction);
        output_file += "_basic_texture.tga";
    }
    else if (shader_choice == ShadersOptions::NormalMappingTexture)
    {
        shader = std::make_unique<Texture>(model, model_view_projection_transform, viewport_matrix, light_direction);
        output_file += "_normal_mapping.tga";
    }
    else if (shader_choice == ShadersOptions::Phong)
    {
        shader = std::make_unique<Phong>(model, model_view_projection_transform, viewport_matrix, light_direction);
        output_file += "_phong.tga";
    }

    for (int i = 0; i < model.number_faces(); ++i)
    {
        std::array<Vector3f, 3> screen_coordinates;
        for (int j = 0; j < 3; ++j)
        {
            screen_coordinates[j] = shader->vertex(i, j);
        }
        
        rasterize(screen_coordinates, *shader, image, depth_buffer);
    }

    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file(output_file.c_str()); 
}

std::string parse_filename(const std::string& filename, char target)
{
    const auto target_position = filename.find_last_of(target);
    const std::size_t extension_size = 4;
    
    if (target_position == std::string::npos) 
    {
        return filename.substr(0, filename.size() - extension_size - 1);
    }

    return filename.substr(target_position + 1, filename.size() - target_position - extension_size - 1);
}