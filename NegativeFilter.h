#pragma once

#include "ChannelWiseFilter.h"

class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override = default;

protected:
    void FilterImpl(Image::Channel &channel) const override;
};