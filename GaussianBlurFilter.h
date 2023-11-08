#pragma once

#include "ChannelWiseFilter.h"

using KernelMatrix = std::vector<double>;

class GaussianBlurFilter : public ChannelWiseFilter {
public:
    explicit GaussianBlurFilter(const double sigma);

    ~GaussianBlurFilter() override = default;

    KernelMatrix GetKernel() const;

protected:
    void FilterImpl(Image::Channel& channel) const override;

private:
    double sigma_;
};