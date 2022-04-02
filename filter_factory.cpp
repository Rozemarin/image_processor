#include "filter_factory.h"

#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"

#include "filters/edge_detection_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/gaussian_blur_filter.h"

#include "filters/pixelate_filter.h"

#include <string_view>
#include <stdexcept>

namespace filter_generators {

BaseFilter* MakeNegativeFilter(const FilterDescriptor& d) {
    if (d.name != "neg") {
        throw std::invalid_argument("wrong filter name");
    }
    return new NegativeFilter;
}

BaseFilter* MakeCropFilter(const FilterDescriptor& d) {
    if (d.name != "crop") {
        throw std::invalid_argument("wrong filter name");
    }
    try {
        if (d.params.size() != 2) {
            throw std::exception();
        }
        int32_t new_width = std::stoi(std::string(d.params.at(0)));
        int32_t new_height = std::stoi(std::string(d.params.at(1)));
        if (new_height <= 0 || new_width <= 0) {
            throw std::exception();
        }
        return new CropFilter(new_width, new_height);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong crop params");
    }
}

BaseFilter* MakeGrayscaleFilter(const FilterDescriptor& d) {
    if (d.name != "gs") {
        throw std::invalid_argument("wrong filter name");
    }
    return new GrayscaleFilter;
}

BaseFilter* MakeSharpeningFilter(const FilterDescriptor& d) {
    if (d.name != "sharp") {
        throw std::invalid_argument("wrong filter name");
    }
    return new SharpeningFilter();
}

BaseFilter* MakeEdgeDetectionFilter(const FilterDescriptor& d) {
    if (d.name != "edge") {
        throw std::invalid_argument("wrong filter name");
    }
    try {
        std::string str_threshold(d.params.at(0));
        double threshold = std::stod(str_threshold.c_str());
        if (threshold < 0 || 1 < threshold) {
            throw std::exception();
        }
        return new EdgeDetectionFilter(threshold);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong edge params");
    }
}

BaseFilter* MakeGaussianBlurFilter(const FilterDescriptor& d) {
    if (d.name != "blur") {
        throw std::runtime_error("wrong filter name");
    }
    try {
        std::string str_sigma(d.params.at(0));
        double sigma = std::stod(str_sigma.c_str());
        return new GaussianBlurFilter(sigma);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong blur params");
    }
}

BaseFilter* MakePixelateFilter(const FilterDescriptor& d) {
    if (d.name != "pixel") {
        throw std::exception();
    }
    try {
        std::string str_edge_size(d.params.at(0));
        double edge_size = std::stoi(str_edge_size.c_str());
        return new PixelateFilter(edge_size);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong pixel params");
    }
}

}  // namespace filter_generators

void FilterGeneratorFactory::AddFilterMaker(std::string_view name, FilterGenerator f) {
    mp_[name] = f;
}

FilterGenerator FilterGeneratorFactory::GetFilterMaker(std::string_view name) {
    if (mp_.find(name) != mp_.end()) {
        return mp_[name];
    }

    return nullptr;
}
