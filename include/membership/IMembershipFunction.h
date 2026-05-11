#pragma once
#include "../json/json.hpp"

// Интерфейс для всех функций принадлежности нечетких множеств.
class IMembershipFunction
{
public:
    virtual ~IMembershipFunction() = default;

    // Возвращает степень принадлежности значения x к нечеткому множеству.
    [[nodiscard]] virtual double getMembership(double x) const = 0;

    // Сериализация функции принадлежности в JSON.
    [[nodiscard]] virtual nlohmann::json serialize() const = 0;
};
