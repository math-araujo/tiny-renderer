#ifndef MODEL_HPP
#define MODEL_HPP

#include "geometry.hpp"
#include <string>
#include <vector>

class Model
{
public:
    explicit Model(const std::string& filename);
    int number_vertices() const;
    int number_faces() const;
    Vector3f& vertex(int id);
    const Vector3f& vertex(int id) const;
    std::vector<int>& face(int id);
    const std::vector<int>& face(int id) const;
private:
    std::vector<Vector3f> vertices_;
    std::vector<std::vector<int>> faces_;
};

#endif // MODEL_HPP