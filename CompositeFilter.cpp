#include "CompositeFilter.h"

CompositeFilter::CompositeFilter(AllFilters filters) : filters_(std::move(filters)) {
}

void CompositeFilter::ApplyFilter(Image &image) const {
    for (const auto &filter : filters_) {
        filter->ApplyFilter(image);
    }
}

void CompositeFilter::AddFilter(std::unique_ptr<AbstractFilter> filter_ptr) {
    filters_.push_back(std::move(filter_ptr));
}