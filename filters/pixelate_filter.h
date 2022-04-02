#pragma once

#include "base_filter.h"

class PixelateFilter : public BaseFilter {
public:
    PixelateFilter(int32_t square_edge);
    void Apply(Image& image) override;
private:
    int32_t square_edge_ = 0;
};