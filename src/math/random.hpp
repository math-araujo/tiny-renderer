#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cmath>
#include <random>

// Returns a random double in range [0.0; 1.0[
inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// Returns a random double in range [min; max[
inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

// Returns a random integer in range [min; max]
inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max + 1));
}

inline unsigned char random_uchar()
{
    return static_cast<unsigned char>(random_double(0, 256));
}

#endif // RANDOM_HPP