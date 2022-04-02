#include "helper.h"

#include <iostream>

const std::string BASE_HELP_TEXT =
    "Use the following syntax: {program_name} {input_file} {output_file} [-{filter1} [params_for_filter1] ...] ...\n"
    "------------------------\n"
    "List of filters:\n"
    "Crop (-crop width height)\n"
    "Grayscale (-gs)\n"
    "Negative (-neg)\n"
    "Sharpening (-sharp)\n"
    "Edge Detection (-edge threshold) (0 < threshold < 1)\n"
    "Gaussian Blur (-blur sigma)\n"
    "Pixelate (pixel_size)";

void BaseHelper() {
    std::cout << BASE_HELP_TEXT;
}

void FilterNameHelper(std::string_view filter_name) {
    std::cout << "Error: " << filter_name << ". No filter found." << std::endl;
}

void ExceptionHelper(std::exception& exception) {
    std::cout << exception.what() << std::endl;
}
