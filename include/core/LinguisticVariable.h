#pragma once
#include <string>
#include <map>
#include <memory>
#include "membership/IMembershipFunction.h"

// Лингвистическая переменная, содержащая набор термов (нечетких множеств).
class LinguisticVariable
{
private:
    std::string name;                                                  // Имя переменной (например, "Рентабельность")
    std::map<std::string, std::shared_ptr<IMembershipFunction>> terms; // Набор термов (например, "Низкая", "Высокая")

public:
    explicit LinguisticVariable(std::string varName) : name(std::move(varName)) {}

    // Добавление нового терма и связанной с ним функции принадлежности
    void addTerm(const std::string &termName, std::shared_ptr<IMembershipFunction> function)
    {
        terms[termName] = std::move(function);
    }

    // Получение функции принадлежности по имени терма
    [[nodiscard]] std::shared_ptr<IMembershipFunction> getTerm(const std::string &termName) const
    {
        if (auto it = terms.find(termName); it != terms.end())
        {
            return it->second;
        }
        return nullptr;
    }

    // Возвращает имя лингвистической переменной
    [[nodiscard]] std::string getName() const { return name; }
};