#include <catch.hpp>

#include "image.h"

TEST_CASE("SwapEndian") {
    unsigned int a = 0xAABBCCDD;
    auto b = SwapEndian(a);

    REQUIRE(b == 0xDDCCBBAA);
    b = SwapEndian(b);

    REQUIRE(b == a);
}

TEST_CASE("LoadWriteQuteImage") {
    auto i1 = Image("./tests/test_pictures/example.bmp");
    REQUIRE(i1.bmp_info_header.height == 12);
    i1.WriteBMP("./tests/test_pictures/out_example.bmp");
    auto i2 = Image("./tests/test_pictures/out_example.bmp");
    REQUIRE(i2.bmp_info_header.colors_important == i1.bmp_info_header.colors_important);
}

TEST_CASE("LoadWriteBMPWithPaddings") {
    auto i1 = Image("./tests/test_pictures/fx.bmp");

    i1.WriteBMP("./tests/test_pictures/out_fx.bmp");
    auto i2 = Image("./tests/test_pictures/out_fx.bmp");

    REQUIRE(i1.bmp_info_header.height == i2.bmp_info_header.height);
    REQUIRE(i1.bmp_file_header.offset_data == i2.bmp_file_header.offset_data);
}