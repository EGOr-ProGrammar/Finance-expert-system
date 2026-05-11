#pragma once
#include <string>

// Представляет атомарное условие вида "x это A", где x - переменная, A - терм.
struct Condition
{
    std::string variableName; // Имя входной лингвистической переменной (например, "Спрос")
    std::string termName;     // Имя терма (например, "Низкий")

    Condition(std::string var, std::string term)
        : variableName(std::move(var)), termName(std::move(term)) {}
};