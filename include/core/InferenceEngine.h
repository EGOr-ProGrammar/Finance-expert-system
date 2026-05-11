#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include "Rule.h"
#include "defuz/IDefuzzifier.h"
#include "operators/ITNorm.h"
#include "LinguisticVariable.h"

/**
 * @class InferenceEngine
 * @brief Ядро экспертной системы, координирующее процесс нечеткого вывода.
 * * Класс реализует структуру системы нечеткого вывода с фаззификатором и 
 * дефаззификатором согласно модели Мамдани-Заде[cite: 256, 271].
 */
class InferenceEngine {
private:
    std::map<std::string, LinguisticVariable> variables;
    std::vector<Rule> rules;
    
    // Карта центров выходных термов: Имя_Переменной -> (Имя_Терма -> Значение_Центра)
    // Используется для дефаззификации по методу среднего центра [cite: 444-445].
    std::map<std::string, std::map<std::string, double>> outputTermCenters;

    // Стратегии агрегации и дефаззификации (Паттерн "Стратегия")
    std::shared_ptr<ITNorm> tNorm;
    std::shared_ptr<IDefuzzifier> defuzzifier;

public:
    /**
     * @brief Конструктор механизма вывода.
     * @param norm Стратегия T-нормы (например, MinTNorm для логического произведения) [cite: 238-239].
     * @param defuzz Стратегия дефаззификации (например, CenterAverageDefuzzifier)[cite: 456].
     */
    InferenceEngine(std::shared_ptr<ITNorm> norm, std::shared_ptr<IDefuzzifier> defuzz)
        : tNorm(std::move(norm)), defuzzifier(std::move(defuzz)) {}

    /**
     * @brief Регистрация лингвистической переменной в системе.
     */
    void addVariable(const LinguisticVariable& var) {
        variables.insert({var.getName(), var});
    }

    /**
     * @brief Добавление правила в базу знаний[cite: 467].
     */
    void addRule(const Rule& rule) {
        rules.push_back(rule);
    }

    /**
     * @brief Регистрация центра выходного терма (y_ci) для процесса дефаззификации.
     */
    void registerOutputTermCenter(const std::string& varName, const std::string& termName, double center) {
        outputTermCenters[varName][termName] = center;
    }

    /**
     * @brief Выполнение нечеткого логического вывода на основе входных фактов.
     * * Процесс состоит из вычисления истинности посылок, активации правил и 
     * последующей скаляризации результата [cite: 468-474].
     * * @param facts Словарь четких входных значений (Имя_Переменной -> Значение).
     * @return std::map<std::string, double> Дефаззифицированные выходные значения.
     */
    [[nodiscard]] std::map<std::string, double> infer(const std::map<std::string, double>& facts) const {
        // Группировка результатов: Выходная_Переменная -> список пар {Уровень_Активации, Центр_Терма}
        std::map<std::string, std::vector<std::pair<double, double>>> aggregatedOutputs;

        for (const auto& rule : rules) {
            // 1. Вычисление уровня активации правила (антецедента) 
            double activationLevel = rule.evaluate(facts, variables, *tNorm);
            
            if (activationLevel > 0.0) {
                std::string outVar = rule.getOutputVariable();
                std::string outTerm = rule.getOutputTerm();
                
                // 2. Поиск центра выходного значения (консеквента) для правила
                auto varIt = outputTermCenters.find(outVar);
                if (varIt != outputTermCenters.end()) {
                    auto termIt = varIt->second.find(outTerm);
                    if (termIt != varIt->second.end()) {
                        double center = termIt->second;
                        // Сохраняем пару для дефаззификации
                        aggregatedOutputs[outVar].emplace_back(activationLevel, center);
                    }
                }
            }
        }

        // 3. Дефаззификация: переход от нечетких представлений к четким
        std::map<std::string, double> results;
        for (const auto& [varName, activations] : aggregatedOutputs) {
            results[varName] = defuzzifier->defuzzify(activations);
        }

        return results;
    }
};