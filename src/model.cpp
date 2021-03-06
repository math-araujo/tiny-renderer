#include "model.hpp"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

Model::Model(const std::string& filename)
{
    std::ifstream input_file{filename};
    
    if (input_file.is_open())
    {
        std::string line;

        while (std::getline(input_file, line))
        {
            std::istringstream stream{line};
            char trash;

            if (line.compare(0, 2, "v ") == 0)
            {
                stream >> trash;
                Vector3f vertex;
                stream >> vertex;
                vertices_.emplace_back(vertex);
            }
            else if (line.compare(0, 2, "f ") == 0)
            {
                stream >> trash;
                std::vector<FaceElement> face;
                int vertex_index;
                int texture_index;
                int normal_index;

                while (stream >> vertex_index >> trash >> texture_index >> trash >> normal_index)
                {
                    face.emplace_back(vertex_index - 1, texture_index - 1, normal_index - 1);
                }
                assert(face.size() == 3);
                
                faces_.emplace_back(std::move(face));
            }
            else if (line.compare(0, 3, "vt ") == 0)
            {
                stream >> trash >> trash;
                Vector2f uv;
                stream >> uv;
                uv_coordinates_.emplace_back(std::move(uv));
            }
            else if (line.compare(0, 3, "vn ") == 0)
            {
                stream >> trash >> trash;
                Vector3f normal;
                stream >> normal;
                normal_vectors_.emplace_back(std::move(normal));
            }
        }
        
        std::cerr << "Vertices: " << vertices_.size() << " Faces: " << faces_.size() 
                  << " Texture vertices: " << uv_coordinates_.size()
                  << " Normal vectors: " << normal_vectors_.size() << "\n";
        
        load_model_texture(filename, "_diffuse.tga", diffuse_map_);
    }
}

int Model::number_vertices() const 
{
    return static_cast<int>(vertices_.size());
}

int Model::number_faces() const 
{
    return static_cast<int>(faces_.size());
}

Vector3f& Model::vertex(int id)
{
    return vertices_[id];
}

const Vector3f& Model::vertex(int id) const
{
    return vertices_[id];
}

Vector3f& Model::vertex(int face, int vertex_number)
{
    const auto vertex_index = faces_[face][vertex_number].vertex_index;
    return vertices_[vertex_index];
}

const Vector3f& Model::vertex(int face, int vertex_number) const
{
    const auto vertex_index = faces_[face][vertex_number].vertex_index;
    return vertices_[vertex_index];
}

std::vector<int> Model::face(int id) const
{
    std::vector<int> faces_vertices;
    faces_vertices.reserve(faces_[id].size());

    for (const auto& face: faces_[id])
    {
        faces_vertices.emplace_back(face.vertex_index);
    }

    return faces_vertices;
}

std::vector<FaceElement>& Model::face_element(int id)
{
    return faces_[id];
}

const std::vector<FaceElement>& Model::face_element(int id) const
{
    return faces_[id];
}

Vector2f Model::uv(int face, int vertex)
{
    const auto index = faces_[face][vertex].texture_index;
    return uv(index);
}

Vector2f Model::uv(int index)
{
    return uv_coordinates_[index];
}

TGAColor Model::diffuse_map_at(Vector2f uv)
{
    Vector2i uv_screen{static_cast<int>(uv.x * diffuse_map_.get_width()),
                       static_cast<int>(uv.y * diffuse_map_.get_height())};
    return diffuse_map_.get(uv_screen.x, uv_screen.y);
}

Vector3f& Model::normal(int face, int vertex)
{
    const auto index = faces_[face][vertex].normal_index;
    return normal(index);
}

const Vector3f& Model::normal(int face, int vertex) const
{
    const auto index = faces_[face][vertex].normal_index;
    return normal(index);
}

Vector3f& Model::normal(int index)
{
    return normal_vectors_[index];
}

const Vector3f& Model::normal(int index) const
{
    return normal_vectors_[index];
}

void load_model_texture(std::string filename, std::string suffix, TGAImage& image)
{
    std::size_t dot_pos = filename.find_last_of(".");
    if (dot_pos == std::string::npos)
    {
        return;
    }

    std::string texture_file{filename.substr(0, dot_pos) + suffix};
    std::cerr << "Texture file " << texture_file << " loading " << (image.read_tga_file(texture_file.c_str()) ? "success" : "failed") << std::endl;
    image.flip_vertically();
}