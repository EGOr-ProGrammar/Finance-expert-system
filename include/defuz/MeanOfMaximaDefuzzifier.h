#pragma once
#include "IDefuzzifier.h"
#include <algorithm>

// Дефаззификация относительно среднего максимума (Mean of Maxima) [cite: 446-449].
class MeanOfMaximaDefuzzifier final : public IDefuzzifier
{
public:
    [[nodiscard]] double defuzzify(const std::vector<std::pair<double, double>> &activatedRules) const override
    {
        if (activatedRules.empty())
            return 0.0;

        // Поиск максимального уровня активации
        double maxMu = 0.0;
        for (const auto &rule : activatedRules)
        {
            if (rule.first > maxMu)
            {
                maxMu = rule.first;
            }
        }

        if (maxMu == 0.0)
            return 0.0;

        // Вычисление среднего значения среди центров с максимальной активацией
        double sumCenters = 0.0;
        int count = 0;

        for (const auto &rule : activatedRules)
        {
            // Сравнение с плавающей точкой через epsilon
            if (std::abs(rule.first - maxMu) < 1e-9)
            {
                sumCenters += rule.second;
                count++;
            }
        }

        return (count > 0) ? (sumCenters / static_cast<double>(count)) : 0.0;
    }
};