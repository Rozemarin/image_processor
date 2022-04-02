#include "parser_cmd.h"

#include <cstring>

bool ParserCmd::Parse(int argc, char** argv) {
    if (argc <= MIN_PARAM_NUM) {
        return false;
    }
    input_file_name_ = argv[INPUT_FILE_NAME_POS];
    output_file_name_ = argv[OUTPUT_FILE_NAME_POS];
    if (argv[OUTPUT_FILE_NAME_POS + 1][0] != '-') {
        return false;
    }
    FilterDescriptor tmp_filter_descriptor;
    for (int i = OUTPUT_FILE_NAME_POS + 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (!tmp_filter_descriptor.name.empty()) {
                filters_to_apply.push_back(tmp_filter_descriptor);
            }
            std::string_view filter = std::string_view(argv[i]).substr(1, std::strlen(argv[i]));
            tmp_filter_descriptor.name = filter;
            tmp_filter_descriptor.params = {};
        } else {
            tmp_filter_descriptor.params.push_back(argv[i]);
        }
    }
    if (!tmp_filter_descriptor.name.empty()) {
        filters_to_apply.push_back(tmp_filter_descriptor);
    }
    return true;
}

std::string ParserCmd::GetInputFileName() const {
    return std::string{input_file_name_};
}

std::string ParserCmd::GetOutputFileName() const {
    return std::string{output_file_name_};
}