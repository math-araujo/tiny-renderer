#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

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

    Vector2& operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& operator*=(T scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2& operator/=(T scale)
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

    Vector3& operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator*=(T scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vector3& operator/=(T scale)
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
inline Vector2<T> operator*(T scale, const Vector2<T>& v)
{
    return Vector2<T>{scale * v.x, scale * v.y};
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& v, T scale)
{
    return scale * v;
}

template<typename T>
inline Vector2<T> operator/(T scale, const Vector2<T>& v)
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
inline Vector3<T> operator*(T scale, const Vector3<T>& v)
{
    return Vector3<T>{scale * v.x, scale * v.y, scale * v.z};
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& v, T scale)
{
    return scale * v;
}

template<typename T>
inline Vector3<T> operator/(T scale, const Vector3<T>& v)
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

#endif // GEOMETRY_HPP