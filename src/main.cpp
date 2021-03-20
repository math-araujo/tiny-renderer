#include "scenes.hpp"

int main(int argc, char* argv[])
{
    std::string filename{"obj/african_head/african_head.obj"};
    if (argc == 2)
    {
        filename = argv[1];
    }

    Scenes scenes{filename};
    scenes.draw_wire_mesh();
    scenes.draw_random_colored_triangles();
    scenes.draw_back_face_culling();
    scenes.draw_depth_buffer();
    scenes.draw_textured_depth_buffer();
    scenes.draw_perspective_projection();
    scenes.draw_gouraud_shading();
    scenes.draw_look_at();
    scenes.draw_our_gl(ShadersOptions::Gouraud);
    scenes.draw_our_gl(ShadersOptions::BasicTexture);
    scenes.draw_our_gl(ShadersOptions::NormalMappingTexture);
    scenes.draw_our_gl(ShadersOptions::Phong);

    return 0;
}