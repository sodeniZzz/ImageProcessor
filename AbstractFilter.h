#pragma once

#include "Image.h"

class AbstractFilter {
public:
    virtual void ApplyFilter(Image &image) const = 0;

    virtual ~AbstractFilter() = default;
};