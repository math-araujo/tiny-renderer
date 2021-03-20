#ifndef SCENES_HPP
#define SCENES_HPP

#include "tgaimage.h"
#include "trianglemesh.hpp"
#include "vector.hpp"
#include <string>

// List of available shaders
enum class ShadersOptions
{
    Gouraud,
    BasicTexture,
    NormalMappingTexture,
    Phong
};

Vector3i world_to_screen(Vector3f pos, int width, int heigth);

class Scenes
{
public:
    Scenes(const std::string& filename, int image_width = 600, int image_height = 600);
    
    // Chapter 1 final render: wire frame mesh
    void draw_wire_mesh();

    // Chapter 2 render: triangles filled with random colors
    void draw_random_colored_triangles();

    // Chapter 2 final render: triangles filled with colors proportional to lighthing intensity
    void draw_back_face_culling();

    // Chapter 3 final render: model with back face culling and depth buffering 
    void draw_depth_buffer();

    // Chapter 3 homework: add textures to draw_depth_buffer
    void draw_textured_depth_buffer();

    // Chapter 4: perspective projection
    void draw_perspective_projection();

    // Chapter 5: Gouraud shading
    void draw_gouraud_shading();

    // Chapter 5: perspective projection with camera transformation
    void draw_look_at();

    // Chapter 6: Our GL with shaders
    void draw_our_gl(ShadersOptions shader_choice = ShadersOptions::NormalMappingTexture);

private:
    TriangleMesh model;
    std::string model_name;
    const int width;
    const int height;
    const int depth{255};
    TGAImage image;
};

std::string parse_filename(const std::string& filename, char target = '/');

#endif // SCENES_HPP