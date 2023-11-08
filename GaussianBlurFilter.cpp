#include "GaussianBlurFilter.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(const double sigma) : sigma_(sigma) {
}

KernelMatrix GaussianBlurFilter::GetKernel() const {
    int32_t size = static_cast<int32_t>(std::ceil(3 * sigma_)) * 2 + 1;
    KernelMatrix kernel(size);
    double sum_coefficients = 0.0;
    for (int32_t i = 0; i < size; ++i) {
        double coef = 1 / (2 * M_PI * sigma_ * sigma_) *
                      std::pow(M_E, -((i - size / 2) * (i - size / 2)) / (2 * sigma_ * sigma_));
        kernel[i] = coef;
        sum_coefficients += coef;
    }
    for (int32_t i = 0; i < size; ++i) {
        kernel[i] /= sum_coefficients;
    }
    return kernel;
}

void GaussianBlurFilter::FilterImpl(Image::Channel& channel) const {
    const int32_t width = static_cast<int32_t>(channel[0].size());
    const int32_t height = static_cast<int32_t>(channel.size());

    Image::Channel filtered_channel(height, std::vector<double>(width, 0.0));

    KernelMatrix kernel = GetKernel();
    const int32_t radius = static_cast<int32_t>(std::ceil(3 * sigma_));

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            for (int32_t d = -radius; d <= radius; ++d) {
                filtered_channel[y][x] += channel[y][std::max(0, std::min(width - 1, x + d))] * kernel[d + radius];
            }
        }
    }
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            double sum = 0.0;
            for (int32_t d = -radius; d <= radius; ++d) {
                sum += filtered_channel[std::max(0, std::min(height - 1, y + d))][x] * kernel[d + radius];
            }
            channel[y][x] = sum;
        }
    }
}