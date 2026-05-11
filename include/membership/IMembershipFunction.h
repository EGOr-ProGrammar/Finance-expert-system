#pragma once

// Интерфейс для всех функций принадлежности нечетких множеств.
class IMembershipFunction
{
public:
    virtual ~IMembershipFunction() = default;

    // Возвращает степень принадлежности значения x к нечеткому множеству.
    [[nodiscard]] virtual double getMembership(double x) const = 0;
};