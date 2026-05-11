#pragma once
#include "ITNorm.h"

// Форма алгебраического произведения
class ProductTNorm final : public ITNorm
{
public:
    [[nodiscard]] double evaluate(const std::vector<double> &values) const override
    {
        if (values.empty())
            return 0.0;
        double result = 1.0;
        for (double val : values)
        {
            result *= val;
        }
        return result;
    }

    [[nodiscard]] double evaluate(double a, double b) const override
    {
        return a * b;
    }
};