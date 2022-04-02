#pragma once

#include "base_filter.h"
#include "matrix_for_filters.h"

class SharpeningFilter : public BaseFilter {
public:
    void Apply(Image &image) override;

private:
    const Matrix matrix_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};
