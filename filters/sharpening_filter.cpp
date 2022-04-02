#include "sharpening_filter.h"

void SharpeningFilter::Apply(Image& image) {
    ApplyMatrix(matrix_, image);
}