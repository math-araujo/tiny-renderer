#include "model.hpp"

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
                std::vector<int> face;
                int itrash;
                int idx;
                while (stream >> idx >> trash >> itrash >> trash >> itrash)
                {
                    --idx;
                    face.emplace_back(idx);
                }

                faces_.emplace_back(std::move(face));
            }
        }
        
        std::cerr << "Vertices: " << vertices_.size() << " Faces: " << faces_.size() << "\n";
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

std::vector<int>& Model::face(int id)
{
    return faces_[id];
}

const std::vector<int>& Model::face(int id) const
{
    return faces_[id];
}