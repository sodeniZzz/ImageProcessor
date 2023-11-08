#pragma once

#include "AbstractFilter.h"
#include "Image.h"

class CropFilter : public AbstractFilter {
public:
    CropFilter(const uint32_t width, const uint32_t height);

    void ApplyFilter(Image& image) const override;

    ~CropFilter() override = default;

private:
    uint32_t height_;
    uint32_t width_;
};