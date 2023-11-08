#include "CropFilter.h"

CropFilter::CropFilter(const uint32_t width, const uint32_t height) : height_(height), width_(width) {
}

void CropFilter::ApplyFilter(Image& image) const {
    auto& channels = image.GetChannels();
    const uint32_t old_height = image.GetHeight();
    const uint32_t old_width = image.GetWidth();
    const uint32_t new_height = std::min(old_height, height_);
    const uint32_t new_width = std::min(old_width, width_);
    for (Image::Channel& channel : channels) {
        channel.resize(new_height);
        for (auto& row : channel) {
            row.resize(new_width);
        }
    }
    image.SetSize(new_width, new_height);
}
