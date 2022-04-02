#include <catch.hpp>
#include "filters/crop_filter.h"
#include "filters/negative_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/pixelate_filter.h"

// SQUARE IMAGES WITHOUT PADDINGS

TEST_CASE("TestNegFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/neg_example.bmp");

    NegativeFilter filter = NegativeFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestGsFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/gs_example.bmp");

    GrayscaleFilter filter = GrayscaleFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestCropFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/crop_example.bmp");

    CropFilter filter = CropFilter(8, 8);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestSharpFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/sharp_example.bmp");

    SharpeningFilter filter = SharpeningFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestEdgeFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/edge_example.bmp");

    EdgeDetectionFilter filter = EdgeDetectionFilter(0.03);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestBlurFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/blur_example.bmp");

    GaussianBlurFilter filter = GaussianBlurFilter(2);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPixelFilter") {
    Image i = Image("./tests/test_pictures/example.bmp");
    Image target = Image("./tests/test_pictures/pixel_example.bmp");

    PixelateFilter filter = PixelateFilter(5);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

// NOT SQUARE IMAGES WITH PADDINGS

TEST_CASE("TestPaddingNegFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_neg_example.bmp");

    NegativeFilter filter = NegativeFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPaddingGsFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_gs_example.bmp");

    GrayscaleFilter filter = GrayscaleFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPaddingCropFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_crop_example.bmp");

    CropFilter filter = CropFilter(1, 7);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPaddingSharpFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_sharp_example.bmp");

    SharpeningFilter filter = SharpeningFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPaddingEdgeFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_edge_example.bmp");

    EdgeDetectionFilter filter = EdgeDetectionFilter(0.03);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPaddingBlurFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_blur_example.bmp");

    GaussianBlurFilter filter = GaussianBlurFilter(2);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}

TEST_CASE("TestPaddingPixelFilter") {
    Image i = Image("./tests/test_pictures/padding_example.bmp");
    Image target = Image("./tests/test_pictures/padding_pixel_example.bmp");

    PixelateFilter filter = PixelateFilter(2);
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}