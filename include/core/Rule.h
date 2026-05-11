#pragma once
#include <vector>
#include <string>
#include <map>
#include "Condition.h"
#include "LinguisticVariable.h"
#include "operators/ITNorm.h"

class Rule
{
private:
    std::vector<Condition> conditions; // Левая часть (антецеденты)
    std::string outputVariableName;    // Имя выходной переменной
    std::string outputTermName;        // Имя выходного терма (консеквент)

public:
    Rule(std::string outVar, std::string outTerm)
        : outputVariableName(std::move(outVar)), outputTermName(std::move(outTerm)) {}

    void addCondition(const std::string &varName, const std::string &termName)
    {
        conditions.emplace_back(varName, termName);
    }

    [[nodiscard]] double evaluate(
        const std::map<std::string, double> &facts,
        const std::map<std::string, LinguisticVariable> &variables,
        const ITNorm &tNorm) const
    {
        if (conditions.empty())
            return 0.0;

        std::vector<double> membershipValues;
        membershipValues.reserve(conditions.size());

        for (const auto &cond : conditions)
        {
            auto factIt = facts.find(cond.variableName);
            auto varIt = variables.find(cond.variableName);

            if (factIt == facts.end() || varIt == variables.end()) return 0.0;

            auto termFunc = varIt->second.getTerm(cond.termName);
            if (!termFunc) return 0.0;

            membershipValues.push_back(termFunc->getMembership(factIt->second));
        }

        return tNorm.evaluate(membershipValues);
    }

    [[nodiscard]] std::string getOutputVariable() const { return outputVariableName; }
    [[nodiscard]] std::string getOutputTerm() const { return outputTermName; }
    
    // Геттер для условий (нужен для сериализации и отображения)
    [[nodiscard]] const std::vector<Condition>& getConditions() const {
        return conditions;
    }
};
