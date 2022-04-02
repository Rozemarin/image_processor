cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES
        parser_cmd.cpp
        image.cpp
        helper.cpp
        filter_factory.cpp
        filters/negative_filter.cpp
        filters/crop_filter.cpp
        filters/grayscale_filter.cpp
        filters/sharpening_filter.cpp
        filters/edge_detection_filter.cpp
        filters/gaussian_blur_filter.cpp
        filters/pixelate_filter.cpp
        )

set(TEST_FILES
        tests/test_image.cpp
        tests/test_filters.cpp
        tests/test_parser.cpp
        )

add_executable(image_processor
        image_processor.cpp
        ${SOURCE_FILES}
        )
