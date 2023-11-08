#include <catch.hpp>

#include "Image.h"
#include "CropFilter.h"
#include "GrayScaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"
#include "Pixelate.h"

const double EPS = 0.01;

const int PIXEL_SIZE = 32;
const uint32_t WIDTH = 999;
const uint32_t HEIGHT = 1999;
const double THRESHOLD = 0.1;
const double SIGMA = 7.5;

bool IsEqual(const auto& first, const auto& second) {
    for (size_t k = 0; k < first.size(); ++k) {
        for (size_t i = 0; i < first[k].size(); ++i) {
            for (size_t j = 0; j < first[k][0].size(); ++j) {
                if (std::abs(first[k][i][j] - second[k][i][j]) >= EPS) {
                    return false;
                }
            }
        }
    }
    return true;
}

TEST_CASE("Reading File: invalid format file") {
    std::string input_file = "../tasks/image_processor/test_script/data/invalid_format.txt";
    try {
        Image image(input_file);
    } catch (const std::runtime_error& e) {
        REQUIRE(e.what() == std::string("Error: Input file must be BMP! But this was given:" + input_file));
    }
}

TEST_CASE("Reading File: non exist file") {
    std::string input_file = "../tasks/image_processor/test_script/data/invalid.bmp";
    try {
        Image image(input_file);
    } catch (const std::runtime_error& e) {
        REQUIRE(e.what() == std::string("No such file or directory: " + input_file));
    }
}

TEST_CASE("My filter(Pixelate)") {
    Image my_image("../tasks/image_processor/test_script/data/lenna.bmp");
    PixelateFilter filter(PIXEL_SIZE);
    filter.ApplyFilter(my_image);
    Image lenna_pixelate("../tasks/image_processor/test_script/data/lenna_pixelate.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& lenna_pixelate_channels = lenna_pixelate.GetChannels();
    REQUIRE(IsEqual(my_image_channels, lenna_pixelate_channels));
}

TEST_CASE("Writing File: invalid format file") {
    std::string input_file = "../tasks/image_processor/test_script/data/lenna.bmp";
    std::string output_file = "../tasks/image_processor/test_script/data/invalid_format.txt";
    try {
        Image image(input_file);
        image.BMPWriteFile(output_file);
    } catch (const std::runtime_error& e) {
        REQUIRE(e.what() == std::string("Error: Output file must be BMP! But this was given:" + output_file));
    }
}

TEST_CASE("Writing File: non exist file") {
    std::string input_file = "../tasks/image_processor/test_script/data/lenna.bmp";
    std::string output_file = "../tasks/image_processor/test_script/THISFOLDEREXIST/invalid_format.bmp";
    try {
        Image image(input_file);
        image.BMPWriteFile(output_file);
    } catch (const std::runtime_error& e) {
        REQUIRE(e.what() == std::string("Error: Unable to open the input file: " + output_file));
    }
}

TEST_CASE("Test_CropFilter") {
    Image my_image("../tasks/image_processor/test_script/data/lenna.bmp");
    CropFilter filter(WIDTH, HEIGHT);
    filter.ApplyFilter(my_image);
    Image lenna_crop("../tasks/image_processor/test_script/data/lenna_crop.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& lenna_crop_channels = lenna_crop.GetChannels();
    REQUIRE(IsEqual(my_image_channels, lenna_crop_channels));
}

TEST_CASE("Test_GrayScaleFilter") {
    Image my_image("../tasks/image_processor/test_script/data/lenna.bmp");
    GrayScaleFilter filter;
    filter.ApplyFilter(my_image);
    Image lenna_gs("../tasks/image_processor/test_script/data/lenna_gs.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& lenna_gs_channels = lenna_gs.GetChannels();
    REQUIRE(IsEqual(my_image_channels, lenna_gs_channels));
}

TEST_CASE("Test_NegativeFilter") {
    Image my_image("../tasks/image_processor/test_script/data/lenna.bmp");
    NegativeFilter filter;
    filter.ApplyFilter(my_image);
    Image lenna_neg("../tasks/image_processor/test_script/data/lenna_neg.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& lenna_neg_channels = lenna_neg.GetChannels();
    REQUIRE(IsEqual(my_image_channels, lenna_neg_channels));
}

TEST_CASE("Test_SharpeningFilter") {
    Image my_image("../tasks/image_processor/test_script/data/lenna.bmp");
    SharpeningFilter filter;
    filter.ApplyFilter(my_image);
    Image lenna_sharp("../tasks/image_processor/test_script/data/lenna_sharp.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& lenna_sharp_channels = lenna_sharp.GetChannels();
    REQUIRE(IsEqual(my_image_channels, lenna_sharp_channels));
}

TEST_CASE("Test_EdgeDetectionFilterFilter") {
    Image my_image("../tasks/image_processor/test_script/data/flag.bmp");
    EdgeDetectionFilter filter(THRESHOLD);
    filter.ApplyFilter(my_image);
    Image flag_edge("../tasks/image_processor/test_script/data/flag_edge.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& flag_edge_channels = flag_edge.GetChannels();
    REQUIRE(IsEqual(my_image_channels, flag_edge_channels));
}

TEST_CASE("Test_GaussianBlurFilterFilter") {
    Image my_image("../tasks/image_processor/test_script/data/lenna.bmp");
    GaussianBlurFilter filter(SIGMA);
    filter.ApplyFilter(my_image);
    Image lenna_blur("../tasks/image_processor/test_script/data/lenna_blur.bmp");
    auto& my_image_channels = my_image.GetChannels();
    auto& lenna_blur_channels = lenna_blur.GetChannels();
    REQUIRE(IsEqual(my_image_channels, lenna_blur_channels));
}