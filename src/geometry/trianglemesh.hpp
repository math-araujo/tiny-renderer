#ifndef TRIANGLE_MESH_HPP
#define TRIANGLE_MESH_HPP

#include "tgaimage.h"
#include "vector.hpp"
#include <string>
#include <vector>

/*
In .obj format, each face element contain vertex, texture and normal indices (in this order)
separated by slashes
*/
struct FaceElement
{
    int vertex_index{0};
    int texture_index{0};
    int normal_index{0};

    FaceElement() {}
    FaceElement(int vertex, int texture, int normal): vertex_index{vertex}, texture_index{texture}, normal_index{normal} {}
};

class TriangleMesh
{
public:
    explicit TriangleMesh(const std::string& filename);
    int number_vertices() const;
    int number_faces() const;
    Vector3f& vertex(int id);
    const Vector3f& vertex(int id) const;
    Vector3f& vertex(int face, int vertex_number);
    const Vector3f& vertex(int face, int vertex_number) const;
    std::vector<int> face(int id) const;
    std::vector<FaceElement>& face_element(int id);
    const std::vector<FaceElement>& face_element(int id) const;
    Vector2f& uv(int face, int vertex);
    const Vector2f& uv(int face, int vertex) const;
    Vector2f& uv(int index);
    const Vector2f& uv(int index) const;
    TGAColor diffuse_map_at(Vector2f uv) const;
    Vector3f& normal(int face, int vertex);
    const Vector3f& normal(int face, int vertex) const;
    Vector3f& normal(int index);
    const Vector3f& normal(int index) const;
    Vector3f normal_map_at(Vector2f uv) const;
    float specular_map_at(Vector2f uv) const;
private:
    std::vector<Vector3f> vertices_;
    std::vector<std::vector<FaceElement>> faces_;
    std::vector<Vector3f> normal_vectors_;

    // For texture coordinates
    std::vector<Vector2f> uv_coordinates_;
    TGAImage diffuse_map_;
    TGAImage normal_map_;
    TGAImage specular_map_;
};

void load_model_texture(std::string filename, std::string suffix, TGAImage& image);

#endif // TRIANGLE_MESH_HPP