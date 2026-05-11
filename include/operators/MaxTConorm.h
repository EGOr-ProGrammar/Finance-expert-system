#pragma once
#include "ITConorm.h"
#include <algorithm>

// Оператор логической суммы (Мах) как агрегатор равнозначных результатов импликации[cite: 283].
class MaxTConorm final : public ITConorm
{
public:
    [[nodiscard]] double evaluate(const std::vector<double> &values) const override
    {
        if (values.empty())
            return 0.0;
        return *std::max_element(values.begin(), values.end());
    }
};