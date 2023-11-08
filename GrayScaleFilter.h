#pragma once

#include "AbstractFilter.h"

const double RED_COEF = 0.299;
const double GREEN_COEF = 0.587;
const double BLUE_COEF = 0.114;

class GrayScaleFilter final : public AbstractFilter {
public:
    ~GrayScaleFilter() override = default;

    void ApplyFilter(Image& image) const final;
};