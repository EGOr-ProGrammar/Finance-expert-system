#pragma once
#include <vector>
#include <map>
#include <string>
#include "LinguisticVariable.h"
#include "Rule.h"

/**
 * @class KnowledgeBase
 * @brief Хранилище лингвистических переменных и правил экспертной системы. (Model)
 */
class KnowledgeBase {
private:
    std::map<std::string, LinguisticVariable> variables;
    std::vector<Rule> rules;
    
    // Карта центров выходных термов: Имя_Переменной -> (Имя_Терма -> Значение_Центра)
    std::map<std::string, std::map<std::string, double>> outputTermCenters;

public:
    void addVariable(const LinguisticVariable& var) {
        variables.insert({var.getName(), var});
    }

    void addRule(const Rule& rule) {
        rules.push_back(rule);
    }

    void registerOutputTermCenter(const std::string& varName, const std::string& termName, double center) {
        outputTermCenters[varName][termName] = center;
    }

    [[nodiscard]] const std::map<std::string, LinguisticVariable>& getVariables() const { return variables; }
    [[nodiscard]] const std::vector<Rule>& getRules() const { return rules; }
    [[nodiscard]] const std::map<std::string, std::map<std::string, double>>& getOutputTermCenters() const { return outputTermCenters; }
    
    // Поиск центров для конкретной переменной
    [[nodiscard]] const std::map<std::string, double>* getTermCenters(const std::string& varName) const {
        auto it = outputTermCenters.find(varName);
        if (it != outputTermCenters.end()) return &it->second;
        return nullptr;
    }
};
