#pragma once
#include "IMembershipFunction.h"
#include <cmath>

// Обобщенная гауссовская функция принадлежности.
class GeneralizedGaussianFunction final : public IMembershipFunction
{
private:
    double center; // Параметр c
    double sigma;  // Параметр sigma
    double b;      // Параметр b (влияет на форму кривой)

public:
    GeneralizedGaussianFunction(double c, double s, double b_val)
        : center(c), sigma(s), b(b_val) {}

    // Расчет по формуле mu(x) = exp(-((x-c)/sigma)^(2b))
    [[nodiscard]] double getMembership(double x) const override
    {
        if (sigma == 0.0)
            return (x == center) ? 1.0 : 0.0;
        double arg = std::abs((x - center) / sigma); // Модуль предотвращает NaN при дробном 2b и отрицательном основании
        return std::exp(-std::pow(arg, 2.0 * b));
    }
};