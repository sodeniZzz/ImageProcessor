set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.24)

project(image_processor)

add_executable(
        image_processor
        image_processor.cpp
        AbstractFilter.h Image.cpp Image.h CropFilter.cpp CropFilter.h GrayScaleFilter.cpp GrayScaleFilter.h
        NegativeFilter.cpp NegativeFilter.h ChannelWiseFilter.cpp ChannelWiseFilter.h ConvFilter.cpp ConvFilter.h
        SharpeningFilter.cpp SharpeningFilter.h ThresholdFilter.cpp ThresholdFilter.h EdgeDetectionFilter.cpp
        EdgeDetectionFilter.h CompositeFilter.cpp CompositeFilter.h GaussianBlurFilter.cpp GaussianBlurFilter.h
        Pixelate.cpp Pixelate.h ParseAndHelp.h)
