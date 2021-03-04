#include "matrix.hpp"
#include <cassert>

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