#pragma once
#include <vector>

// Интерфейс для T-норм (оператор И). Применяется для агрегирования предпосылок и на уровне импликации.
class ITNorm
{
public:
    virtual ~ITNorm() = default;

    // Агрегирование многомерного вектора условий
    [[nodiscard]] virtual double evaluate(const std::vector<double> &values) const = 0;

    // Вычисление импликации для двух значений (предпосылка и заключение)
    [[nodiscard]] virtual double evaluate(double a, double b) const = 0;
};