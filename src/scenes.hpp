#ifndef SCENES_HPP
#define SCENES_HPP

#include "vector.hpp"
#include <string>

Vector3i world_to_screen(Vector3f pos, int width, int heigth);

// Chapter 1 final render: wire frame mesh
void draw_wire_mesh(const std::string& filename);

// Chapter 2 render: triangles filled with random colors
void draw_random_colored_triangles(const std::string& filename);

// Chapter 2 final render: triangles filled with colors proportional to lighthing intensity
void draw_back_face_culling(const std::string& filename);

// Chapter 3 final render: model with back face culling and depth buffering 
void draw_depth_buffer(const std::string& filename);

// Chapter 3 homework: add textures to draw_depth_buffer
void draw_textured_depth_buffer(const std::string& filename);

// Chapter 4: perspective projection
void draw_perspective_projection(const std::string& filename);

// Chapter 5: Gouraud shading
void draw_gouraud_shading(const std::string& filename);

// Chapter 5: perspective projection with camera transformation
void draw_look_at(const std::string& filename);

// Chapter 6: Our GL with shaders
void draw_our_gl(const std::string& filename);

#endif // SCENES_HPP