#pragma once

#include "base_filter.h"

class GrayscaleFilter : public BaseFilter {
public:
    void Apply(Image &image) override;
};
