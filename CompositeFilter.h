#pragma once

#include "AbstractFilter.h"

#include "memory"

class CompositeFilter : public AbstractFilter {
public:
    using AllFilters = std::vector<std::unique_ptr<AbstractFilter>>;
    ~CompositeFilter() override = default;

    explicit CompositeFilter(AllFilters filters);

    void ApplyFilter(Image &image) const override;

    void AddFilter(std::unique_ptr<AbstractFilter> filter_ptr);

private:
    AllFilters filters_;
};