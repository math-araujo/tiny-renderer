#ifndef MATHEMATICAL_VECTOR_HPP
#define MATHEMATICAL_VECTOR_HPP

#include <cmath>
#include <iostream>
#include <type_traits>

// SFINAE to allow only numeric types
template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
struct Vector2
{
    T x{0};
    T y{0};

    Vector2() {}
    Vector2(T x, T y): x{x}, y{y} {}
    
    T& operator[](std::size_t index)
    {
        if (index == 0)
        {
            return x;
        }
        else if (index == 1)
        {
            return y;
        }

        std::cerr << "ERROR: index " << index << " out of range on Vector2<T>::operator[]\n";
        return x; // meaningless...
    }
    
    const T& operator[](std::size_t index) const 
    {
        if (index == 0)
        {
            return x;
        }
        else if (index == 1)
        {
            return y;
        }

        std::cerr << "ERROR: index " << index << " out of range on Vector2<T>::operator[]\n";
        return x; // meaningless...
    }

    Vector2& operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& operator*=(double scale)
    {
        x = static_cast<T>(scale * x);
        y = static_cast<T>(scale * y);
        return *this;
    }

    Vector2& operator/=(double scale)
    {
        *this *= 1 / scale;
        return *this;
    }

    Vector2& normalize()
    {
        *this *= 1 / length();
        return *this;
    }

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const 
    {
        return x * x + y * y;
    }
};

template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
struct Vector3
{
    T x{0};
    T y{0};
    T z{0};

    Vector3() {}
    Vector3(T x, T y, T z): x{x}, y{y}, z{z} {}

    T& operator[](std::size_t index)
    {
        if (index == 0)
        {
            return x;
        }
        else if (index == 1)
        {
            return y;
        }
        else if (index == 2)
        {
            return z;
        }

        std::cerr << "ERROR: index " << index << " out of range on Vector3<T>::operator[]\n";
        return x; // meaningless...
    }

    const T& operator[](std::size_t index) const
    {
        if (index == 0)
        {
            return x;
        }
        else if (index == 1)
        {
            return y;
        }
        else if (index == 2)
        {
            return z;
        }

        std::cerr << "ERROR: index " << index << " out of range on Vector3<T>::operator[]\n";
        return x; // meaningless...
    }

    Vector3& operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator*=(double scale)
    {
        x = static_cast<T>(scale * x);
        y = static_cast<T>(scale * y);
        z = static_cast<T>(scale * z);
        return *this;
    }

    Vector3& operator/=(double scale)
    {
        *this *= 1 / scale;
        return *this;
    }

    Vector3& normalize()
    {
        *this *= 1 / length();
        return *this;
    }

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const 
    {
        return x * x + y * y + z * z;
    }
};

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<int>;

template<typename TTarget, typename TFrom>
Vector2<TTarget> cast(const Vector2<TFrom>& vector)
{
    return Vector2<TTarget>{static_cast<TTarget>(vector.x), 
                            static_cast<TTarget>(vector.y)};
}

template<typename TTarget, typename TFrom>
Vector3<TTarget> cast(const Vector3<TFrom>& vector)
{
    return Vector3<TTarget>{static_cast<TTarget>(vector.x), 
                            static_cast<TTarget>(vector.y), 
                            static_cast<TTarget>(vector.z)};
}

template<typename T>
inline Vector2<T> operator+(const Vector2<T>& u, const Vector2<T>& v)
{
    return Vector2<T>{u.x + v.x, u.y + v.y};
}

template<typename T>
inline Vector2<T> operator-(const Vector2<T>& u, const Vector2<T>& v)
{
    return Vector2<T>{u.x - v.x, u.y - v.y};
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& u, const Vector2<T>& v)
{
    return Vector2<T>{u.x * v.x, u.y * v.y};
}

template<typename T>
inline Vector2<T> operator*(double scale, const Vector2<T>& v)
{
    return Vector2<T>{static_cast<T>(scale * v.x), static_cast<T>(scale * v.y)};
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& v, double scale)
{
    return scale * v;
}

template<typename T>
inline Vector2<T> operator/(const Vector2<T>& v, double scale)
{
    return (1 / scale) * v;
}

template<typename T>
inline bool operator==(const Vector2<T>& u, const Vector2<T>& v)
{
    return u.x == v.x && u.y == v.y;
}

template<typename T>
inline bool operator!=(const Vector2<T>& u, const Vector2<T>& v)
{
    return !(u == v);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& output, const Vector2<T>& v)
{
    return output << v.x << ' ' << v.y;;
}

template<typename T>
inline std::istream& operator>>(std::istream& input, Vector2<T>& v)
{
    return input >> v.x >> v.y;
}

template<typename T>
inline Vector2<T> unit_vector(const Vector2<T>& v)
{
    return v / v.length();
}

template<typename T>
inline double dot(const Vector2<T>& u, const Vector2<T>& v)
{
    return u.x * v.x + u.y * v.y;
}

// Vector3<T> functions

template<typename T>
inline Vector3<T> operator+(const Vector3<T>& u, const Vector3<T>& v)
{
    return Vector3<T>{u.x + v.x, u.y + v.y, u.z + v.z};
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& u, const Vector3<T>& v)
{
    return Vector3<T>{u.x - v.x, u.y - v.y, u.z - v.z};
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& u, const Vector3<T>& v)
{
    return Vector3<T>{u.x * v.x, u.y * v.y, u.z * v.z};
}

template<typename T>
inline Vector3<T> operator*(double scale, const Vector3<T>& v)
{
    return Vector3<T>{static_cast<T>(scale * v.x), static_cast<T>(scale * v.y), static_cast<T>(scale * v.z)};
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& v, double scale)
{
    return scale * v;
}

template<typename T>
inline Vector3<T> operator/(const Vector3<T>& v, double scale)
{
    return (1 / scale) * v;
}

template<typename T>
inline bool operator==(const Vector3<T>& u, const Vector3<T>& v)
{
    return u.x == v.x && u.y == v.y && u.z == v.z;
}

template<typename T>
inline bool operator!=(const Vector3<T>& u, const Vector3<T>& v)
{
    return !(u == v);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& output, const Vector3<T>& v)
{
    return output << v.x << ' ' << v.y << ' ' << v.z;
}

template<typename T>
inline std::istream& operator>>(std::istream& input, Vector3<T>& v)
{
    return input >> v.x >> v.y >> v.z;
}

template<typename T>
inline Vector3<T> unit_vector(const Vector3<T>& v)
{
    return v / v.length();
}

template<typename T>
inline double dot(const Vector3<T>& u, const Vector3<T>& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template<typename T>
inline Vector3<T> cross(const Vector3<T>& u, const Vector3<T>& v)
{
    return Vector3<T>{u.y * v.z - u.z * v.y,
                    u.z * v.x - u.x * v.z,
                    u.x * v.y - u.y * v.x};
}

#endif // MATHEMATICAL_VECTOR