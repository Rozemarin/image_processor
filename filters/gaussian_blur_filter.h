#pragma once

#include "base_filter.h"
#include "matrix_for_filters.h"

class GaussianBlurFilter : public BaseFilter {
public:
    GaussianBlurFilter(double sigma);

    DoubleMatrix GenerateGaussMatrix();
    void Apply(Image& image) override;
private:
    double sigma_ = 0;
};

