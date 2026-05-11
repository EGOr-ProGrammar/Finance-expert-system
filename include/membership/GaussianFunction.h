#pragma once
#include "IMembershipFunction.h"
#include <cmath>

// Гауссовская функция принадлежности.
class GaussianFunction final : public IMembershipFunction
{
private:
    double center; // Параметр c (центр)
    double sigma;  // Параметр sigma (вариация/крутизна)

public:
    GaussianFunction(double c, double s) : center(c), sigma(s) {}

    // Расчет по формуле mu(x) = exp(-((x-c)/sigma)^2)
    [[nodiscard]] double getMembership(double x) const override
    {
        if (sigma == 0.0)
            return (x == center) ? 1.0 : 0.0;
        double arg = (x - center) / sigma;
        return std::exp(-(arg * arg));
    }
};