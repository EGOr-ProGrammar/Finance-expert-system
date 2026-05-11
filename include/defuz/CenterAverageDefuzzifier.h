#pragma once
#include "IDefuzzifier.h"

// Дефаззификация относительно среднего центра (Center Average) [cite: 444-445].
class CenterAverageDefuzzifier final : public IDefuzzifier
{
public:
    [[nodiscard]] double defuzzify(const std::vector<std::pair<double, double>> &activatedRules) const override
    {
        double sumMuY = 0.0;
        double sumMu = 0.0;

        for (const auto &rule : activatedRules)
        {
            double mu = rule.first;
            double center = rule.second;
            sumMuY += mu * center;
            sumMu += mu;
        }

        return (sumMu > 0.0) ? (sumMuY / sumMu) : 0.0;
    }
};