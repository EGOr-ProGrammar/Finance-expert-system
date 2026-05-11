#pragma once
#include <vector>

// Интерфейс для T-конорм (оператор ИЛИ). Применяется для агрегирования результатов вывода многих правил.
class ITConorm
{
public:
    virtual ~ITConorm() = default;

    // Вычисление результирующего нечеткого множества (или уровня активации)
    [[nodiscard]] virtual double evaluate(const std::vector<double> &values) const = 0;
};