#include <catch.hpp>
#include <string>

#include "../parser_cmd.h"

TEST_CASE("TestParser") {
    std::vector<std::string> arguments = {"a.out",
                                          "./tests/test_pictures/example.bmp",
                                          "./tests/test_pictures/output.bmp",
                                          "-sharp",
                                          "-edge",
                                          "0.123",
                                          "-crop",
                                          "100",
                                          "200"};

    std::vector<char*> argv;
    for (const auto& arg : arguments) {
        argv.push_back((char*)(arg.data()));
    }
    argv.push_back(nullptr);

    ParserCmd parser;
    parser.Parse(argv.size() - 1, &argv[0]);

    REQUIRE(parser.GetInputFileName() == "./tests/test_pictures/example.bmp");
    REQUIRE(parser.GetOutputFileName() == "./tests/test_pictures/output.bmp");

    REQUIRE(parser.filters_to_apply.size() == 3);

    FilterDescriptor sharp = {"sharp", {}};
    FilterDescriptor edge = {"edge", {"0.123"}};
    FilterDescriptor crop = {"crop", {"100", "200"}};
    std::vector<FilterDescriptor> filters_to_apply{sharp, edge, crop};

    for (size_t i = 0; i < 3; ++i) {
        REQUIRE(parser.filters_to_apply.at(i).name == filters_to_apply.at(i).name);
        REQUIRE(parser.filters_to_apply.at(i).params == filters_to_apply.at(i).params);
    }
}
