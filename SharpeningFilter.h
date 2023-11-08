#pragma once

#include "ConvFilter.h"

class SharpeningFilter : public ConvFilter {
public:
    SharpeningFilter();
    ~SharpeningFilter() override = default;
};
