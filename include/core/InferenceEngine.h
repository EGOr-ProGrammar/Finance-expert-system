#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "KnowledgeBase.h"
#include "defuz/IDefuzzifier.h"
#include "operators/ITNorm.h"

/**
 * @class InferenceEngine
 * @brief Сервис для выполнения нечеткого логического вывода. (Logic Layer)
 */
class InferenceEngine {
private:
    // Стратегии агрегации и дефаззификации
    std::shared_ptr<ITNorm> tNorm;
    std::shared_ptr<IDefuzzifier> defuzzifier;

public:
    InferenceEngine(std::shared_ptr<ITNorm> norm, std::shared_ptr<IDefuzzifier> defuzz)
        : tNorm(std::move(norm)), defuzzifier(std::move(defuzz)) {}

    /**
     * @brief Выполнение нечеткого логического вывода на основе базы знаний и фактов.
     * @param kb База знаний.
     * @param facts Словарь четких входных значений.
     * @return std::map<std::string, double> Дефаззифицированные выходные значения.
     */
    [[nodiscard]] std::map<std::string, double> infer(const KnowledgeBase& kb, const std::map<std::string, double>& facts) const {
        std::map<std::string, std::vector<std::pair<double, double>>> aggregatedOutputs;

        for (const auto& rule : kb.getRules()) {
            double activationLevel = rule.evaluate(facts, kb.getVariables(), *tNorm);
            
            if (activationLevel > 0.0) {
                std::string outVar = rule.getOutputVariable();
                std::string outTerm = rule.getOutputTerm();
                
                auto centers = kb.getTermCenters(outVar);
                if (centers) {
                    auto termIt = centers->find(outTerm);
                    if (termIt != centers->end()) {
                        aggregatedOutputs[outVar].emplace_back(activationLevel, termIt->second);
                    }
                }
            }
        }

        std::map<std::string, double> results;
        for (const auto& [varName, activations] : aggregatedOutputs) {
            results[varName] = defuzzifier->defuzzify(activations);
        }

        return results;
    }
};
