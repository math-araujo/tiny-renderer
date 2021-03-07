#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"
#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix();
    Matrix(int number_rows, int number_columns);
    explicit Matrix(std::vector<std::vector<float>>&& initializer);
    inline int number_rows() const;
    inline int number_columns() const;
    std::vector<float>& operator[](int i);
    const std::vector<float>& operator[](int i) const;
    void fill_row(int row, Vector3f vector);
    void fill_row(int row, Vector2f vector);
    void fill_column(int column, Vector3f vector);
    void fill_column(int column, Vector2f vector);
private:
    std::vector<std::vector<float>> data;
    int rows{0};
    int columns{0};
};

bool operator==(const Matrix& lhs, const Matrix& rhs);
bool operator!=(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Vector3f operator*(const Matrix& matrix, const Vector3f& vector);
Matrix operator*(float scale, const Matrix& matrix);
Matrix operator*(const Matrix& matrix, float scale);
Matrix operator/(const Matrix& matrix, float scale);
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);
std::istream& operator>>(std::istream& stream, Matrix& matrix);

Matrix identity(int dimensions);
Matrix transpose(const Matrix& matrix);
Matrix inverse_4x4(const Matrix& matrix);
Matrix inverse_3x3(const Matrix& matrix);

#endif // MATRIX_HPP