#include "ChannelWiseFilter.h"

void ChannelWiseFilter::ApplyFilter(Image& image) const {
    for (Image::Channel& channel : image.GetChannels()) {
        FilterImpl(channel);
    }
}