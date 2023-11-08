#pragma once

#include "ChannelWiseFilter.h"

#include <vector>

using Matrix3x3 = std::vector<std::vector<double>>;

class ConvFilter : public ChannelWiseFilter {
public:
    explicit ConvFilter(const Matrix3x3 &matrix);

    ~ConvFilter() override = default;

protected:
    void FilterImpl(Image::Channel &channel) const final;

private:
    Matrix3x3 matrix_;
};