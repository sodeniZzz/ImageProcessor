#include "ConvFilter.h"
#include <cmath>

ConvFilter::ConvFilter(const Matrix3x3 &matrix) : matrix_(matrix) {
}

void ConvFilter::FilterImpl(Image::Channel &channel) const {
    const ssize_t width = static_cast<int>(channel[0].size());
    const ssize_t height = static_cast<int>(channel.size());

    Image::Channel filtered_channel(height, std::vector<double>(width, 0.0));

    const ssize_t left_board = 0;
    const ssize_t right_board = width - 1;
    const ssize_t upper_board = 0;
    const ssize_t lower_board = height - 1;

    for (ssize_t y = 0; y < channel.size(); ++y) {
        for (ssize_t x = 0; x < channel[y].size(); ++x) {
            filtered_channel[y][x] =
                std::min(1.0, std::max(0.0, matrix_[0][1] * channel[y][std::max(x - 1, left_board)] +
                                                matrix_[1][0] * channel[std::max(y - 1, upper_board)][x] +
                                                matrix_[1][1] * channel[y][x] +
                                                matrix_[1][2] * channel[std::min(y + 1, lower_board)][x] +
                                                matrix_[2][1] * channel[y][std::min(x + 1, right_board)]));
        }
    }
    channel = filtered_channel;
}