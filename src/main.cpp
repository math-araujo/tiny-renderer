#include "tgaimage.h"

int main()
{
    const TGAColor white{255, 255, 255, 255};
    const TGAColor red{255, 0, 0, 255};
    
    TGAImage image{100, 100, TGAImage::RGB};
    image.set(52, 41, red);
    image.flip_vertically(); // set origin to left bottom corner
    image.write_tga_file("output.tga");

    return 0;
}