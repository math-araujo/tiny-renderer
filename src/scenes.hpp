#ifndef SCENES_HPP
#define SCENES_HPP

#include "geometry.hpp"
#include <string>

Vector3f world_to_screen(Vector3f pos, int width, int heigth);

// Chapter 1 final render: wire frame mesh
void draw_wire_mesh(const std::string& filename);

// Chapter 2 render: triangles filled with random colors
void draw_random_colored_wire_mesh(const std::string& filename);

// Chapter 2 final render: triangles filled with colors proportional to lighthing intensity
void draw_back_face_culling_wire_mesh(const std::string& filename);

void draw_depth_buffer(const std::string& filename);

#endif // SCENES_HPP