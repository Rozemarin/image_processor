#include "filters/base_filter.h"
#include "parser_cmd.h"

#include <map>
#include <string_view>

using FilterGenerator = BaseFilter* (*)(const FilterDescriptor&);

class FilterGeneratorFactory {
public:
    void AddFilterMaker(std::string_view name, FilterGenerator f);
    FilterGenerator GetFilterMaker(std::string_view name);

private:
    std::map<std::string_view, FilterGenerator> mp_;
};

namespace filter_generators {
BaseFilter* MakeNegativeFilter(const FilterDescriptor& d);
BaseFilter* MakeCropFilter(const FilterDescriptor& d);
BaseFilter* MakeGrayscaleFilter(const FilterDescriptor& d);
BaseFilter* MakeSharpeningFilter(const FilterDescriptor& d);
BaseFilter* MakeEdgeDetectionFilter(const FilterDescriptor& d);
BaseFilter* MakeGaussianBlurFilter(const FilterDescriptor& d);
BaseFilter* MakePixelateFilter(const FilterDescriptor& d);
}  // namespace filter_generators