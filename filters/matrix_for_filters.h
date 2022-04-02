#pragma once

#include "../image.h"

#include <vector>

using Matrix = std::vector<std::vector<int8_t>>;
using DoubleMatrix = std::vector<std::vector<double>>;

template<typename TemplateMatrix>
void ApplyMatrix(const TemplateMatrix& matrix, Image& image) {
    Image new_image = image;

    int32_t sum_m = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            sum_m += matrix[i][j];
        }
    }
    sum_m = 1;

    for (int32_t x = 0; x < image.bmp_info_header.height; ++x) {
        for (int32_t y = 0; y < image.bmp_info_header.width; ++y) {
            double sum_r = 0, sum_g = 0, sum_b = 0;

            for (int i = -(static_cast<int32_t>(matrix.size() / 2)); i <= (static_cast<int32_t>(matrix.size() / 2));
                 ++i) {
                for (int j = -(static_cast<int32_t>(matrix.size() / 2)); j <= (static_cast<int32_t>(matrix.size() / 2));
                     ++j) {
                    int32_t shifted_x = x + i;
                    int32_t shifted_y = y + j;

                    if (shifted_x < 0) {
                        shifted_x = 0;
                    }

                    if (shifted_y < 0) {
                        shifted_y = 0;
                    }

                    if (shifted_x >= image.bmp_info_header.height) {
                        shifted_x = image.bmp_info_header.height - 1;
                    }

                    if (shifted_y >= image.bmp_info_header.width) {
                        shifted_y = image.bmp_info_header.width - 1;
                    }

                    Pixel pixel = image.GetPixel(shifted_x, shifted_y);
                    auto coeff = matrix[matrix.size() / 2 + i][matrix.size() / 2 + j];

                    sum_r += static_cast<double>(pixel.r) * coeff;
                    sum_g += static_cast<double>(pixel.g) * coeff;
                    sum_b += static_cast<double>(pixel.b) * coeff;
                }
            }
            sum_r = std::min(255.0, std::max(0.0, sum_r));
            sum_g = std::min(255.0, std::max(0.0, sum_g));
            sum_b = std::min(255.0, std::max(0.0, sum_b));
            new_image.SetPixel(x, y,
                               {static_cast<uint8_t>(sum_r), static_cast<uint8_t>(sum_g), static_cast<uint8_t>(sum_b)});
        }
    }
    image.pixels = new_image.pixels;
}
