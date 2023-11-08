#include "Pixelate.h"

PixelateFilter::PixelateFilter(const int32_t pixel_size) : pixel_size_(pixel_size) {
}

void PixelateFilter::FilterImpl(Image::Channel& channel) const {
    const int32_t width = static_cast<int32_t>(channel[0].size());
    const int32_t height = static_cast<int32_t>(channel.size());

    Image::Channel filtered_channel(height, std::vector<double>(width, 0.0));

    for (int32_t y = 0; y < height; y += pixel_size_) {
        for (int32_t x = 0; x < width; x += pixel_size_) {
            double sum = 0.0;
            int count = 0;
            for (int32_t j = 0; j < pixel_size_; ++j) {
                for (int32_t i = 0; i < pixel_size_; ++i) {
                    int32_t valid_y = std::max(0, std::min(height - 1, y + j));
                    int32_t valid_x = std::max(0, std::min(width - 1, x + i));
                    sum += channel[valid_y][valid_x];
                    count++;
                }
            }
            double average_color = sum / count;

            // Set the filtered pixel values in the new channel
            for (int32_t j = 0; j < pixel_size_; ++j) {
                for (int32_t i = 0; i < pixel_size_; ++i) {
                    int32_t valid_y = std::max(0, std::min(height - 1, y + j));
                    int32_t valid_x = std::max(0, std::min(width - 1, x + i));
                    filtered_channel[valid_y][valid_x] = average_color;
                }
            }
        }
    }
    channel = filtered_channel;
}
