#include "EdgeDetectionFilter.h"

const Matrix3x3 EDGE_MATRIX3X3 = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

EdgeDetectionFilter::EdgeDetectionFilter(const double threshold) : CompositeFilter({}) {
    AddFilter(std::make_unique<GrayScaleFilter>());
    AddFilter(std::make_unique<ConvFilter>(EDGE_MATRIX3X3));
    AddFilter(std::make_unique<ThresholdFilter>(threshold));
}