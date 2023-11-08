#pragma once

#include <stdexcept>

#include "Image.h"
#include "CropFilter.h"
#include "GrayScaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"
#include "Pixelate.h"

void PrintHelp() {
    const std::string reset = "\033[0m";
    const std::string bold = "\033[1m";
    const std::string green = "\033[92m";
    const std::string yellow = "\033[93m";
    const std::string cyan = "\033[96m";
    const std::string italic = "\033[3m";

    std::cout << bold << cyan << "Описание формата аргументов командной строки:" << reset << std::endl;

    std::cout << green << "{имя программы} {путь к входному файлу} {путь к выходному файлу} "
                          "[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...] ..."
              << reset << std::endl;

    std::cout << bold << cyan << "Например: " << reset << green
              << "./image_processor ../test_script/data/lenna.bmp ../output.bmp -gs -blur 0.5" << reset << std::endl;

    std::cout << bold << yellow << "Доступные фильтры:" << reset << std::endl;
    std::cout << "-crop " << italic << "width height" << reset << std::endl;
    std::cout << "-gs" << std::endl;
    std::cout << "-neg" << std::endl;
    std::cout << "-sharp" << std::endl;
    std::cout << "-edge " << italic << "threshold" << reset << std::endl;
    std::cout << "-blur " << italic << "sigma" << reset << std::endl;
    std::cout << bold << "Мой фильтр: " << reset << "-pixelate " << italic << "pixel_size(степень 2)" << std::endl;
}

void ParsedToFilters(int argc, char** argv, CompositeFilter& filters) {
    size_t i = 3;
    auto argc_t = static_cast<size_t>(argc);
    while (i < argc_t) {
        std::string filter_type = static_cast<std::string>(argv[i++]);
        if (filter_type == "-crop") {
            if (i + 2 <= argc_t) {
                int32_t width = 0;
                int32_t height = 0;
                try {
                    width = std::stoi(static_cast<std::string>(argv[i++]));
                    height = std::stoi(static_cast<std::string>(argv[i++]));
                } catch (std::exception& e) {
                    throw std::invalid_argument("Error! Wrong parameter for EdgeDetectionFilter");
                }
                if (width <= 0 || height <= 0) {
                    throw std::invalid_argument("Error! Width and height must be greater than zero.");
                }
                filters.AddFilter(
                    std::make_unique<CropFilter>(static_cast<uint32_t>(width), static_cast<uint32_t>(height)));
                std::cout << "CropFilter successfully applied" << std::endl;
            } else {
                throw std::invalid_argument("Error! Not enough parameters for CropFilter.");
            }
        } else if (filter_type == "-gs") {
            filters.AddFilter(std::make_unique<GrayScaleFilter>());
            std::cout << "GrayScale successfully applied" << std::endl;
        } else if (filter_type == "-neg") {
            filters.AddFilter(std::make_unique<NegativeFilter>());
            std::cout << "NegativeFilter successfully applied" << std::endl;
        } else if (filter_type == "-sharp") {
            filters.AddFilter(std::make_unique<SharpeningFilter>());
            std::cout << "SharpeningFilter successfully applied" << std::endl;
        } else if (filter_type == "-edge") {
            if (i + 1 <= argc_t) {
                double threshold = 0.0;
                try {
                    threshold = std::stod(static_cast<std::string>(argv[i++]));
                } catch (std::exception& e) {
                    throw std::invalid_argument("Error! Wrong parameter for EdgeDetectionFilter.");
                }
                if (threshold < 0 || threshold > 1) {
                    throw std::invalid_argument("Error! Threshold parameter must be in [0;1].");
                }
                filters.AddFilter(std::make_unique<EdgeDetectionFilter>(threshold));
                std::cout << "EdgeDetectionFilter successfully applied" << std::endl;
            } else {
                throw std::invalid_argument("Error! Not enough parameters for EdgeDetectionFilter.");
            }
        } else if (filter_type == "-blur") {
            if (i + 1 <= argc_t) {
                double sigma = 0.0;
                try {
                    sigma = std::stod(static_cast<std::string>(argv[i++]));
                } catch (std::exception& e) {
                    throw std::invalid_argument("Error! Wrong parameter for BlurFilter.");
                }
                if (sigma < 0) {
                    throw std::invalid_argument("Error! Sigma parameter must be in greater than zero.");
                }
                filters.AddFilter(std::make_unique<GaussianBlurFilter>(sigma));
                std::cout << "BlurFilter successfully applied" << std::endl;
            } else {
                throw std::invalid_argument("Error! Not enough parameters for BlurFilter.");
            }
        } else if (filter_type == "-pixelate") {
            if (i + 1 <= argc_t) {
                int32_t pixel_size = 0;
                try {
                    pixel_size = std::stoi(static_cast<std::string>(argv[i++]));
                } catch (std::exception& e) {
                    throw std::invalid_argument("Error! Wrong parameter for PixelateFilter.");
                }
                if (pixel_size <= 0 || (pixel_size & (pixel_size - 1))) {
                    throw std::invalid_argument("Error! Size of pixel must be a power of 2.");
                }
                filters.AddFilter(std::make_unique<PixelateFilter>(pixel_size));
                std::cout << "PixelateFilter successfully applied" << std::endl;
            } else {
                throw std::invalid_argument("Error! Not enough parameters for PixelateFilter.");
            }
        } else {
            throw std::logic_error("Error! No such filter: " + filter_type);
        }
    }
}
