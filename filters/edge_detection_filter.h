#pragma once

#include "base_filter.h"
#include "matrix_for_filters.h"

class EdgeDetectionFilter : public BaseFilter {
public:
    EdgeDetectionFilter(double threshold);
    void Apply(Image &image) override;

private:
    const Matrix matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    const uint8_t threshold_ = 0;
};

