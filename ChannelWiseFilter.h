#pragma once

#include "AbstractFilter.h"

class ChannelWiseFilter : public AbstractFilter {
public:
    ~ChannelWiseFilter() override = default;

    void ApplyFilter(Image& image) const final;

protected:
    virtual void FilterImpl(Image::Channel& channel) const = 0;
};
