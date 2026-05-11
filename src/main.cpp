#include <iostream>
#include <memory>
#include "core/InferenceEngine.h"
#include "operators/MinTNorm.h"
#include "defuz/CenterAverageDefuzzifier.h"
#include "json/KnowledgeBaseLoader.h"

int main() {
    std::cout << "--- Financial Fuzzy Expert System (Mamdani-Zadeh) ---" << std::endl;

    try {
        // Инициализация ЭС с выбранными стратегиями:
        // Используем логическое произведение (Min) для агрегации условий [cite: 238-239]
        // Используем средний центр для дефаззификации [cite: 444-445, 456]
        auto tNorm = std::make_shared<MinTNorm>();
        auto defuzzifier = std::make_shared<CenterAverageDefuzzifier>();
        InferenceEngine engine(tNorm, defuzzifier);

        // Загрузка базы знаний
        std::cout << "Loading knowledge base..." << std::endl;
        KnowledgeBaseLoader::load("data/knowledge_base.json", engine);

        // Сбор четких фактов от пользователя
        std::map<std::string, double> facts;
        int factCount;
        std::cout << "Number of input facts: ";
        std::cin >> factCount;

        for (int i = 0; i < factCount; ++i) {
            std::string name;
            double val;
            std::cout << "Fact " << i + 1 << " (Name Value): ";
            std::cin >> name >> val;
            facts[name] = val;
        }

        // Логический вывод [cite: 468-474]
        auto results = engine.infer(facts);

        std::cout << "\n--- Inference Results ---" << std::endl;
        if (results.empty()) {
            std::cout << "Warning: No rules were activated." << std::endl;
        } else {
            for (const auto& [varName, value] : results) {
                std::cout << "Output [" << varName << "]: " << value << std::endl;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}