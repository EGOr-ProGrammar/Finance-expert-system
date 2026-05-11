#pragma once
#include <vector>
#include <utility>

// Интерфейс для алгоритмов дефаззификации.
class IDefuzzifier
{
public:
    virtual ~IDefuzzifier() = default;

    // Принимает вектор пар {уровень_активации, центр_терма} и возвращает четкое значение
    [[nodiscard]] virtual double defuzzify(const std::vector<std::pair<double, double>> &activatedRules) const = 0;
};