#pragma once

#include "image.h"

#include <string_view>
#include <vector>

struct FilterDescriptor {
    std::string_view name;
    std::vector<std::string_view> params;
};

class ParserCmd {
public:
    bool Parse(int argc, char* argv[]);
    std::string GetInputFileName() const;
    std::string GetOutputFileName() const;

    std::vector<FilterDescriptor> filters_to_apply;

private:
    std::string_view input_file_name_;
    std::string_view output_file_name_;

    static const int MIN_PARAM_NUM = 3;
    static const int INPUT_FILE_NAME_POS = 1;
    static const int OUTPUT_FILE_NAME_POS = 2;
};
