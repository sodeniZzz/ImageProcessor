#pragma once

#include "ChannelWiseFilter.h"

class ThresholdFilter : public ChannelWiseFilter {
public:
    explicit ThresholdFilter(const double threshold);

    ~ThresholdFilter() override = default;

protected:
    void FilterImpl(Image::Channel& channel) const override;

private:
    double threshold_;
};
