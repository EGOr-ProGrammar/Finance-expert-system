#pragma once
#include <string>
#include <map>
#include <memory>
#include "membership/IMembershipFunction.h"

// Лингвистическая переменная, содержащая набор термов (нечетких множеств).
class LinguisticVariable
{
private:
    std::string name;
    std::map<std::string, std::shared_ptr<IMembershipFunction>> terms;

public:
    explicit LinguisticVariable(std::string varName) : name(std::move(varName)) {}

    void addTerm(const std::string &termName, std::shared_ptr<IMembershipFunction> function)
    {
        terms[termName] = std::move(function);
    }

    [[nodiscard]] std::shared_ptr<IMembershipFunction> getTerm(const std::string &termName) const
    {
        if (auto it = terms.find(termName); it != terms.end())
        {
            return it->second;
        }
        return nullptr;
    }

    [[nodiscard]] std::string getName() const { return name; }
    
    // Геттер для термов (нужен для сериализации и отображения)
    [[nodiscard]] const std::map<std::string, std::shared_ptr<IMembershipFunction>>& getTerms() const {
        return terms;
    }
};
