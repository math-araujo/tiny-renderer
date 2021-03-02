#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix(int number_rows = 4, int number_columns = 4);
    inline int number_rows() const;
    inline int number_columns() const;
    std::vector<float>& operator[](int i);
    const std::vector<float>& operator[](int i) const;
private:
    std::vector<std::vector<float>> data;
    int rows;
    int columns;
};

bool operator==(const Matrix& lhs, const Matrix& rhs);
bool operator!=(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
std::istream& operator>>(std::istream& stream, Matrix& matrix);

Matrix identity(int dimensions);
Matrix transpose(const Matrix& matrix);

#endif // MATRIX_HPP