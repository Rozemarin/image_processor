#pragma once

#include "base_filter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(int32_t new_width, int32_t new_height);
    void Apply(Image &image) override;

private:
    int32_t new_width_ = 0;
    int32_t new_height_ = 0;
};
