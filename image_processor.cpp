#include "filter_factory.h"
#include "image.h"
#include "helper.h"
#include "parser_cmd.h"

int main(int argc, char* argv[]) {
    try {
        ParserCmd parsed;
        if (!parsed.Parse(argc, argv)) {
            BaseHelper();
            return 1;
        }

        Image image(parsed.GetInputFileName());

        auto filter_generator_factory = FilterGeneratorFactory();
        filter_generator_factory.AddFilterMaker("neg", filter_generators::MakeNegativeFilter);
        filter_generator_factory.AddFilterMaker("gs", filter_generators::MakeGrayscaleFilter);
        filter_generator_factory.AddFilterMaker("crop", filter_generators::MakeCropFilter);
        filter_generator_factory.AddFilterMaker("sharp", filter_generators::MakeSharpeningFilter);
        filter_generator_factory.AddFilterMaker("edge", filter_generators::MakeEdgeDetectionFilter);
        filter_generator_factory.AddFilterMaker("blur", filter_generators::MakeGaussianBlurFilter);
        filter_generator_factory.AddFilterMaker("pixel", filter_generators::MakePixelateFilter);

        for (FilterDescriptor descriptor : parsed.filters_to_apply) {
            auto filter_generator = filter_generator_factory.GetFilterMaker(descriptor.name);
            if (filter_generator == nullptr) {
                FilterNameHelper(descriptor.name);
                return 1;
            }

            BaseFilter* filter;

            filter = filter_generator(descriptor);

            filter->Apply(image);
            delete filter;
        }

        image.WriteBMP(parsed.GetOutputFileName());

    } catch (std::exception& exception) {
        ExceptionHelper(exception);
        return 1;
    }

    return 0;
}
