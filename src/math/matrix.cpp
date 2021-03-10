#include "matrix.hpp"
#include <cassert>
#include <exception>

Matrix::Matrix() {}

Matrix::Matrix(int number_rows, int number_columns): 
    data{std::vector<std::vector<float>>(number_rows, std::vector<float>(number_columns, 0.0f))}, rows{number_rows}, columns{number_columns}
{}

Matrix::Matrix(std::vector<std::vector<float>>&& initializer): 
    data{initializer}, rows{static_cast<int>(data.size())}, columns{static_cast<int>(data.back().size())}
{}

int Matrix::number_rows() const
{
    return rows;
}

int Matrix::number_columns() const
{
    return columns;
}

std::vector<float>& Matrix::operator[](int i)
{
    return data[i];
}

const std::vector<float>& Matrix::operator[](int i) const
{
    return data[i];
}

void Matrix::fill_row(int row, Vector3f vector)
{
    for (int j = 0; j < columns; ++j)
    {
        data[row][j] = vector[j];
    }
}

void Matrix::fill_row(int row, Vector2f vector)
{
    for (int j = 0; j < columns; ++j)
    {
        data[row][j] = vector[j];
    }
}

void Matrix::fill_column(int column, Vector3f vector)
{
    for (int i = 0; i < rows; ++i)
    {
        data[i][column] = vector[i];
    }
}

void Matrix::fill_column(int column, Vector2f vector)
{
    for (int i = 0; i < rows; ++i)
    {
        data[i][column] = vector[i];
    }
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.number_rows() != rhs.number_rows() || lhs.number_columns() != rhs.number_columns())
    {
        return false;
    }

    for (int i = 0; i < lhs.number_rows(); ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }

    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
    return !(lhs == rhs);
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.number_columns() == rhs.number_rows());
    Matrix temp{lhs.number_rows(), rhs.number_columns()};
    
    for (int i = 0; i < temp.number_rows(); ++i)
    {
        for (int j = 0; j < temp.number_columns(); ++j)
        {
            for (int k = 0; k < lhs.number_columns(); ++k)
            {
                int di = i + 1; int dj = j + 1; int dk = k + 1;
                temp[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }

    return temp;
}

Vector3f operator*(const Matrix& matrix, const Vector3f& vector)
{
    return Vector3f
    {
        matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z,
        matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z,
        matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z
    };
}

Matrix operator*(float scale, const Matrix& matrix)
{
    Matrix temp{matrix.number_rows(), matrix.number_columns()};
    for (int i = 0; i < matrix.number_rows(); ++i)
    {
        for (int j = 0; j < matrix.number_columns(); ++j)
        {
            temp[i][j] = scale * matrix[i][j];
        }
    }

    return temp;
}

Matrix operator*(const Matrix& matrix, float scale)
{
    return scale * matrix;
}

Matrix operator/(const Matrix& matrix, float scale)
{
    return (1 / scale) * matrix;
}

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
    for (int i = 0; i < matrix.number_rows(); ++i)
    {
        for (int j = 0; j < matrix.number_columns(); ++j)
        {
            stream << matrix[i][j];
            
            if (j != matrix.number_columns() - 1)
            {
                stream << '\t';
            }
        }

        stream << '\n';
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, Matrix& matrix)
{
    for (int i = 0; i < matrix.number_rows(); ++i)
    {
        for (int j = 0; j < matrix.number_columns(); ++j)
        {
            stream >> matrix[i][j];
        }
    }
    
    return stream;
}


Matrix identity(int dimensions)
{
    Matrix temp{dimensions, dimensions};
    for (int i = 0; i < dimensions; ++i)
    {
        for (int j = 0; j < dimensions; ++j)
        {
            temp[i][j] = (i == j ? 1.0f : 0.0f);
        }
    }

    return temp;
}

Matrix transpose(const Matrix& matrix)
{
    Matrix temp{matrix.number_columns(), matrix.number_rows()};

    for (int i = 0; i < matrix.number_rows(); ++i)
    {
        for (int j = 0; j < matrix.number_columns(); ++j)
        {
            temp[j][i] = matrix[i][j];
        }
    }

    return temp;
}

// Source of original implementation: https://stackoverflow.com/a/44446912
Matrix inverse_4x4(const Matrix& matrix)
{
    if (matrix.number_rows() != 4)
    {
        throw std::logic_error("inverse_4x4 requires a 4x4 matrix\n");
    }

    auto A2323 = matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2] ;
    auto A1323 = matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1] ;
    auto A1223 = matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1] ;
    auto A0323 = matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0] ;
    auto A0223 = matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0] ;
    auto A0123 = matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0] ;
    auto A2313 = matrix[1][2] * matrix[3][3] - matrix[1][3] * matrix[3][2] ;
    auto A1313 = matrix[1][1] * matrix[3][3] - matrix[1][3] * matrix[3][1] ;
    auto A1213 = matrix[1][1] * matrix[3][2] - matrix[1][2] * matrix[3][1] ;
    auto A2312 = matrix[1][2] * matrix[2][3] - matrix[1][3] * matrix[2][2] ;
    auto A1312 = matrix[1][1] * matrix[2][3] - matrix[1][3] * matrix[2][1] ;
    auto A1212 = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1] ;
    auto A0313 = matrix[1][0] * matrix[3][3] - matrix[1][3] * matrix[3][0] ;
    auto A0213 = matrix[1][0] * matrix[3][2] - matrix[1][2] * matrix[3][0] ;
    auto A0312 = matrix[1][0] * matrix[2][3] - matrix[1][3] * matrix[2][0] ;
    auto A0212 = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0] ;
    auto A0113 = matrix[1][0] * matrix[3][1] - matrix[1][1] * matrix[3][0] ;
    auto A0112 = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0] ;

    auto det = matrix[0][0] * (matrix[1][1] * A2323 - matrix[1][2] * A1323 + matrix[1][3] * A1223) 
        - matrix[0][1] * (matrix[1][0] * A2323 - matrix[1][2] * A0323 + matrix[1][3] * A0223) 
        + matrix[0][2] * (matrix[1][0] * A1323 - matrix[1][1] * A0323 + matrix[1][3] * A0123) 
        - matrix[0][3] * (matrix[1][0] * A1223 - matrix[1][1] * A0223 + matrix[1][2] * A0123) ;
    
    if (det == 0)
    {
        throw std::logic_error("Cannot invert singular matrix\n");
    }

    det = 1 / det;

    return Matrix
    {{
        {
            det *   (matrix[1][1] * A2323 - matrix[1][2] * A1323 + matrix[1][3] * A1223),
            det * - (matrix[0][1] * A2323 - matrix[0][2] * A1323 + matrix[0][3] * A1223),
            det *   (matrix[0][1] * A2313 - matrix[0][2] * A1313 + matrix[0][3] * A1213),
            det * - (matrix[0][1] * A2312 - matrix[0][2] * A1312 + matrix[0][3] * A1212)
        },
        {
            det * - (matrix[1][0] * A2323 - matrix[1][2] * A0323 + matrix[1][3] * A0223),
            det *   (matrix[0][0] * A2323 - matrix[0][2] * A0323 + matrix[0][3] * A0223),
            det * - (matrix[0][0] * A2313 - matrix[0][2] * A0313 + matrix[0][3] * A0213),
            det *   (matrix[0][0] * A2312 - matrix[0][2] * A0312 + matrix[0][3] * A0212)
        },
        {
            det *   (matrix[1][0] * A1323 - matrix[1][1] * A0323 + matrix[1][3] * A0123),
            det * - (matrix[0][0] * A1323 - matrix[0][1] * A0323 + matrix[0][3] * A0123),
            det *   (matrix[0][0] * A1313 - matrix[0][1] * A0313 + matrix[0][3] * A0113),
            det * - (matrix[0][0] * A1312 - matrix[0][1] * A0312 + matrix[0][3] * A0112)
        },
        {
            det * - (matrix[1][0] * A1223 - matrix[1][1] * A0223 + matrix[1][2] * A0123),
            det *   (matrix[0][0] * A1223 - matrix[0][1] * A0223 + matrix[0][2] * A0123),
            det * - (matrix[0][0] * A1213 - matrix[0][1] * A0213 + matrix[0][2] * A0113),
            det *   (matrix[0][0] * A1212 - matrix[0][1] * A0212 + matrix[0][2] * A0112)
        },
    }};
}

// Source of original implementation: https://stackoverflow.com/a/18504573
Matrix inverse_3x3(const Matrix& matrix)
{
    if (matrix.number_rows() != 3)
    {
        throw std::logic_error("inverse_3x3 requires a 3x3 matrix\n");
    }

    float det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
                matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    if (det == 0)
    {
        throw std::logic_error("Cannot invert singular matrix\n");
    }

    float inv_det = 1.0f / det;

    return Matrix{{
    {
        (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) * inv_det,
        (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * inv_det,
        (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * inv_det
    },
    {
        (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * inv_det,
        (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * inv_det,
        (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) * inv_det
    },
    {
        (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) * inv_det,
        (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) * inv_det,
        (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * inv_det
    }
    }};
}