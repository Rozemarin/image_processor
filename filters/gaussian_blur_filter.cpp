#include "gaussian_blur_filter.h"

#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {}

void GaussianBlurFilter::Apply(Image& image) {
    ApplyMatrix(GenerateGaussMatrix(), image);
}

DoubleMatrix GaussianBlurFilter::GenerateGaussMatrix() {
    int16_t dim = sigma_ * 3;
    DoubleMatrix gauss_matrix(dim * 2 + 1);
    for (auto& vec : gauss_matrix) {
        vec.resize(dim * 2 + 1, 0);
    }

    // generating matrix
    double sum = 0;
    for (auto x = -dim; x <= dim; ++x) {
        for (auto y = -dim; y <= dim; ++y) {
            double exp_num = -(x * x + y * y);
            double exp_denum = (2 * sigma_ * sigma_);

            double e_exp = pow(M_E, exp_num / exp_denum);
            double val = (e_exp / (2 * M_PI * sigma_ * sigma_));

            gauss_matrix[x + dim][y + dim] = val;
            sum += val;
        }
    }

    // normalizing matrix
    for (auto x = 0; x <= dim * 2; ++x) {
        for (auto y = 0; y <= dim * 2; ++y) {
            gauss_matrix[x][y] /= sum;
        }
    }

    return gauss_matrix;
}
