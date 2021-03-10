#include "scenes.hpp"

int main(int argc, char* argv[])
{
    std::string filename{"obj/african_head/african_head.obj"};
    if (argc == 2)
    {
        filename = argv[1];
    }

    draw_wire_mesh(filename);
    draw_random_colored_triangles(filename);
    draw_back_face_culling(filename);
    draw_depth_buffer(filename);
    draw_textured_depth_buffer(filename);
    draw_perspective_projection(filename);
    draw_gouraud_shading(filename);
    draw_look_at(filename);
    draw_our_gl(filename, ShadersOptions::Gouraud);
    draw_our_gl(filename, ShadersOptions::BasicTexture);
    draw_our_gl(filename, ShadersOptions::NormalMappingTexture);
    draw_our_gl(filename, ShadersOptions::Phong);

    return 0;
}