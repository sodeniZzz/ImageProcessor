#include "ThresholdFilter.h"

ThresholdFilter::ThresholdFilter(const double threshold) : threshold_(threshold) {
}

void ThresholdFilter::FilterImpl(Image::Channel &channel) const {
    for (auto &row : channel) {
        for (auto &pixel : row) {
            pixel = (pixel > threshold_ ? 1 : 0);
        }
    }
}
