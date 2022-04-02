#include "pixelate_filter.h"

PixelateFilter::PixelateFilter(int32_t square_edge) : square_edge_(square_edge) {
}

void PixelateFilter::Apply(Image& image) {
    int32_t horizontal_blocks = (image.bmp_info_header.width + square_edge_) / square_edge_;
    int32_t vertical_blocks = (image.bmp_info_header.height + square_edge_) / square_edge_;

    for (int32_t vert_block = 0; vert_block < vertical_blocks; ++vert_block) {
        for (int32_t hor_block = 0; hor_block < horizontal_blocks; ++hor_block) {
            int32_t sum_r = 0;
            int32_t sum_g = 0;
            int32_t sum_b = 0;
            int32_t pixels_in_area = 0;
            for (int32_t x = square_edge_ * vert_block; x < std::min(square_edge_ * (vert_block + 1), image.bmp_info_header.height); ++x) {
                for (int32_t y = hor_block * square_edge_; y < std::min(square_edge_ * (hor_block + 1), image.bmp_info_header.width); ++y) {
                    Pixel pixel = image.GetPixel(x, y);
                    sum_r += pixel.r;
                    sum_g += pixel.g;
                    sum_b += pixel.b;
                    ++pixels_in_area;
                }
            }
            sum_r /= pixels_in_area;
            sum_g /= pixels_in_area;
            sum_b /= pixels_in_area;
            for (int32_t x = square_edge_ * vert_block; x < std::min(square_edge_ * (vert_block + 1), image.bmp_info_header.height); ++x) {
                for (int32_t y = hor_block * square_edge_; y < std::min(square_edge_ * (hor_block + 1), image.bmp_info_header.width); ++y) {
                    image.SetPixel(
                        x, y, {static_cast<uint8_t>(sum_r), static_cast<uint8_t>(sum_g), static_cast<uint8_t>(sum_b)});
                }
            }
        }
    }
}
