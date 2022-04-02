#include "grayscale_filter.h"

void GrayscaleFilter::Apply(Image& image) {
    for (int32_t x = 0; x < image.bmp_info_header.height; ++x) {
        for (int32_t y = 0; y < image.bmp_info_header.width; ++y) {
            Pixel new_pixel = image.GetPixel(x, y);
            new_pixel.r = new_pixel.g = new_pixel.b = 0.229 * new_pixel.r + 0.586 * new_pixel.g + 0.114 * new_pixel.b;
            image.SetPixel(x, y, new_pixel);
        }
    }
}
