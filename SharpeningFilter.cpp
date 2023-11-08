#include "SharpeningFilter.h"

const Matrix3x3 SHARP_MATRIX3X3 = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

SharpeningFilter::SharpeningFilter() : ConvFilter(SHARP_MATRIX3X3) {
}