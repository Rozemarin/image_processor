#pragma once

#include "base_filter.h"

class NegativeFilter : public BaseFilter {
public:
    void Apply(Image &image) override;
};
