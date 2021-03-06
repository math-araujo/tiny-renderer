#ifndef MODEL_HPP
#define MODEL_HPP

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

class Model
{
public:
    explicit Model(const std::string& filename);
    int number_vertices() const;
    int number_faces() const;
    Vector3f& vertex(int id);
    const Vector3f& vertex(int id) const;
    Vector3f& vertex(int face, int vertex_number);
    const Vector3f& vertex(int face, int vertex_number) const;
    std::vector<int> face(int id) const;
    std::vector<FaceElement>& face_element(int id);
    const std::vector<FaceElement>& face_element(int id) const;
    Vector2f uv(int face, int vertex);
    Vector2f uv(int index);
    TGAColor diffuse_map_at(Vector2f uv);
    Vector3f& normal(int face, int vertex);
    const Vector3f& normal(int face, int vertex) const;
    Vector3f& normal(int index);
    const Vector3f& normal(int index) const;
private:
    std::vector<Vector3f> vertices_;
    std::vector<std::vector<FaceElement>> faces_;
    std::vector<Vector3f> normal_vectors_;

    // For texture coordinates
    std::vector<Vector2f> uv_coordinates_;
    TGAImage diffuse_map_;
};

void load_model_texture(std::string filename, std::string suffix, TGAImage& image);

#endif // MODEL_HPP