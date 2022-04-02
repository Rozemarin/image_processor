#include "image.h"

#include <bit>
#include <fstream>
#include <iostream>
#include <string_view>

Image::Image(const std::string &path) {
    std::ifstream reader(path, std::ios_base::binary);

    if (!reader) {
        throw std::invalid_argument("Unable to read file");
    }

    reader.read(reinterpret_cast<char *>(&bmp_file_header), sizeof(BMPFileHeader));

    if constexpr (std::endian::native == std::endian::big) {
        bmp_file_header.offset_data = SwapEndian(bmp_file_header.offset_data);
        bmp_file_header.magic_bytes = SwapEndian(bmp_file_header.magic_bytes);
        bmp_file_header.file_size = SwapEndian(bmp_file_header.file_size);
    }

    if (bmp_file_header.magic_bytes != BMP_MAGIC_BYTES) {
        throw std::invalid_argument("Wrong file format");
    }
    reader.read(reinterpret_cast<char *>(&bmp_info_header), sizeof(BMPInfoHeader));

    if constexpr (std::endian::native == std::endian::big) {
        bmp_info_header.size = SwapEndian(bmp_info_header.size);
        bmp_info_header.width = SwapEndian(bmp_info_header.width);
        bmp_info_header.height = SwapEndian(bmp_info_header.height);
        bmp_info_header.planes = SwapEndian(bmp_info_header.planes);
        bmp_info_header.bits_per_pixel = SwapEndian(bmp_info_header.bits_per_pixel);
        bmp_info_header.compression = SwapEndian(bmp_info_header.compression);
        bmp_info_header.image_size = SwapEndian(bmp_info_header.image_size);
        bmp_info_header.x_pixels_per_m = SwapEndian(bmp_info_header.x_pixels_per_m);
        bmp_info_header.y_pixels_per_m = SwapEndian(bmp_info_header.y_pixels_per_m);
        bmp_info_header.colors_used = SwapEndian(bmp_info_header.colors_used);
        bmp_info_header.colors_important = SwapEndian(bmp_info_header.colors_important);
    }

    if (bmp_info_header.size != 40) {  // not BITMAPINFOHEADER
        throw std::invalid_argument("Unsupported BMP bitmap header");
    }

    reader.seekg(bmp_file_header.offset_data, reader.beg);
    pixels.resize(bmp_info_header.width * bmp_info_header.height * 3);

    if (bmp_info_header.width % 4 == 0) {
        reader.read(reinterpret_cast<char *>(pixels.data()), pixels.size());
    } else {
        size_t padding = bmp_info_header.width % 4;
        for (int32_t i = 0; i < bmp_info_header.height; ++i) {
            reader.read(reinterpret_cast<char *>(pixels.data() + i * 3 * bmp_info_header.width),
                        bmp_info_header.width * 3);
            reader.seekg(padding, std::ios::cur);
        }
    }

    bmp_file_header.file_size = sizeof(bmp_file_header) + sizeof(bmp_info_header) + pixels.size();
    bmp_file_header.offset_data = sizeof(bmp_file_header) + sizeof(bmp_info_header);
}

void Image::WriteBMP(const std::string &path) {
    std::ofstream writer(path, std::ios_base::binary);

    if (!writer) {
        throw std::invalid_argument("Unable to write file");
    }

    if constexpr (std::endian::native == std::endian::big) {
        bmp_file_header.offset_data = SwapEndian(bmp_file_header.offset_data);
        bmp_file_header.magic_bytes = SwapEndian(bmp_file_header.magic_bytes);
        bmp_file_header.file_size = SwapEndian(bmp_file_header.file_size);

        bmp_info_header.size = SwapEndian(bmp_info_header.size);
        bmp_info_header.width = SwapEndian(bmp_info_header.width);
        bmp_info_header.height = SwapEndian(bmp_info_header.height);
        bmp_info_header.planes = SwapEndian(bmp_info_header.planes);
        bmp_info_header.bits_per_pixel = SwapEndian(bmp_info_header.bits_per_pixel);
        bmp_info_header.compression = SwapEndian(bmp_info_header.compression);
        bmp_info_header.image_size = SwapEndian(bmp_info_header.image_size);
        bmp_info_header.x_pixels_per_m = SwapEndian(bmp_info_header.x_pixels_per_m);
        bmp_info_header.y_pixels_per_m = SwapEndian(bmp_info_header.y_pixels_per_m);
        bmp_info_header.colors_used = SwapEndian(bmp_info_header.colors_used);
        bmp_info_header.colors_important = SwapEndian(bmp_info_header.colors_important);
    }

    writer.write(reinterpret_cast<char *>(&bmp_file_header), sizeof(BMPFileHeader));
    writer.write(reinterpret_cast<char *>(&bmp_info_header), sizeof(BMPInfoHeader));

    if (bmp_info_header.width % 4 == 0) {
        writer.write(reinterpret_cast<char *>(pixels.data()), pixels.size());
    } else {
        size_t padding = bmp_info_header.width % 4;
        char padding_rubbish[] = {0, 0, 0};
        for (int32_t i = 0; i < bmp_info_header.height; ++i) {
            writer.write(reinterpret_cast<char *>(pixels.data() + i * 3 * bmp_info_header.width),
                         bmp_info_header.width * 3);
            writer.write(padding_rubbish, padding);
        }
    }

    writer.flush();
    writer.close();
}

Pixel Image::GetPixel(int32_t x, int32_t y) {
    uint8_t b = pixels[x * bmp_info_header.width * 3 + 3 * y + 0];
    uint8_t g = pixels[x * bmp_info_header.width * 3 + 3 * y + 1];
    uint8_t r = pixels[x * bmp_info_header.width * 3 + 3 * y + 2];
    return {r, g, b};
}

void Image::SetPixel(int32_t x, int32_t y, Pixel new_pixel) {
    pixels[x * bmp_info_header.width * 3 + 3 * y + 0] = new_pixel.b;
    pixels[x * bmp_info_header.width * 3 + 3 * y + 1] = new_pixel.g;
    pixels[x * bmp_info_header.width * 3 + 3 * y + 2] = new_pixel.r;
}

void Image::Resize(int32_t width, int32_t height) {
    if (height > bmp_info_header.height || width > bmp_info_header.width || height <= 0 || width <= 0) {
        return;
    }
    std::vector<uint8_t> new_pixels;
    for (int32_t i = bmp_info_header.height - height; i < bmp_info_header.height; ++i) {
        for (int32_t j = 0; j < width * 3; ++j) {
            new_pixels.push_back(pixels[i * bmp_info_header.width * 3 + j]);
        }
    }
    pixels = new_pixels;
    bmp_info_header.height = height;
    bmp_info_header.width = width;
    bmp_file_header.file_size = bmp_file_header.file_size - bmp_info_header.image_size + width * height * 3;
    bmp_info_header.image_size = width * height * 3;
}
