#include "GrayScaleFilter.h"

void GrayScaleFilter::ApplyFilter(Image& image) const {
    auto& channels = image.GetChannels();

    if (channels.size() == 2) {
        std::cerr << "Unable to apply grayscale filter" << std::endl;
        return;
    } else if (channels.size() == 3) {
        for (size_t y = 0; y < channels[0].size(); ++y) {
            for (size_t x = 0; x < channels[0][y].size(); ++x) {
                channels[0][y][x] = channels[1][y][x] = channels[2][y][x] =
                    RED_COEF * channels[0][y][x] + GREEN_COEF * channels[1][y][x] + BLUE_COEF * channels[2][y][x];
            }
        }
        channels.pop_back();
        channels.pop_back();
    }
}