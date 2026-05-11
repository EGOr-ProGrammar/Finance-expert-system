#pragma once
#include "ITNorm.h"
#include <algorithm>

// Форма логического произведения (оператор Min)[cite: 239, 247].
class MinTNorm final : public ITNorm
{
public:
    [[nodiscard]] double evaluate(const std::vector<double> &values) const override
    {
        if (values.empty())
            return 0.0;
        return *std::min_element(values.begin(), values.end());
    }

    [[nodiscard]] double evaluate(double a, double b) const override
    {
        return std::min(a, b);
    }
};