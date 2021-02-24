#include "tgaimage.h"
#include <algorithm>
#include <cmath>

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
    bool steep = false;
    /*If the height is greater than the width, it's necessary to
    rewrite the loop such as x = ay + b instead of y = ax + b.
    Instead of duplicating the code, it's easier to simple swap
    x and y values.
    */
    if (std::abs(x1 - x0) < std::abs(y1 - y0))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1) // Ensure that the line is draw left to right
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    /*
    Derivation for the formulas and algorithm:
    https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Derivation
    
    Janke - Mathematical Structures for Computer Graphics, Chapter 10, Section 1.
    */
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    const int increment = 2 * std::abs(dy);
    int cumulative_error = 0;
    int y = y0;
    for (int x = x0; x <= x1; ++x)
    {
        if (steep) // higher than wider
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }

        cumulative_error += increment;
        
        if (cumulative_error > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            cumulative_error -= 2 * dx;
        }
    }
}

int main()
{   
    TGAImage image{100, 100, TGAImage::RGB};
    const TGAColor white{255, 255, 255, 255};
    const TGAColor red{255, 0, 0, 255};
    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, red);
    line(80, 40, 13, 20, image, red);
    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("output.tga");

    return 0;
}