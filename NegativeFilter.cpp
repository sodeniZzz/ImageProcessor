#include "NegativeFilter.h"

void NegativeFilter::FilterImpl(Image::Channel &channel) const {
    for (auto &row : channel) {
        for (auto &pixel : row) {
            pixel = 1 - pixel;
        }
    }
}