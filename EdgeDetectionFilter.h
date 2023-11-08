#pragma once

#include "CompositeFilter.h"
#include "ConvFilter.h"
#include "ThresholdFilter.h"
#include "GrayScaleFilter.h"

class EdgeDetectionFilter : public CompositeFilter {
public:
    ~EdgeDetectionFilter() override = default;

    explicit EdgeDetectionFilter(const double threshold);
};