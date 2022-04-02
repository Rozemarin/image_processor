#include "crop_filter.h"

CropFilter::CropFilter(int32_t new_width, int32_t new_height) {
    new_width_ = new_width;
    new_height_ = new_height;
}

void CropFilter::Apply(Image& image) {
    image.Resize(new_width_, new_height_);
}
