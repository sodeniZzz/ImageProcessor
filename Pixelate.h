#pragma once

#include "ChannelWiseFilter.h"

class PixelateFilter : public ChannelWiseFilter {
public:
    explicit PixelateFilter(const int32_t pixel_size);

    ~PixelateFilter() override = default;

protected:
    void FilterImpl(Image::Channel& channel) const override;

private:
    int32_t pixel_size_;
};