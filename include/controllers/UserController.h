#pragma once
#include <memory>
#include "core/KnowledgeBase.h"
#include "core/InferenceEngine.h"
#include "presentation/UserView.h"
#include "json/KnowledgeBaseLoader.h"
#include "operators/MinTNorm.h"
#include "defuz/CenterAverageDefuzzifier.h"

class UserController {
private:
    KnowledgeBase kb;
    UserView view;
    std::string kbPath;

public:
    UserController(std::string path) : kbPath(std::move(path)) {}

    void run() {
        view.showHeader();
        try {
            KnowledgeBaseLoader::load(kbPath, kb);
        } catch (const std::exception& e) {
            view.showMessage("Error loading knowledge base: " + std::string(e.what()));
            return;
        }

        auto tNorm = std::make_shared<MinTNorm>();
        auto defuzzifier = std::make_shared<CenterAverageDefuzzifier>();
        InferenceEngine engine(tNorm, defuzzifier);

        std::map<std::string, double> facts;
        // Identify input variables (those that have membership functions)
        for (const auto& [name, var] : kb.getVariables()) {
            if (!var.getTerms().empty()) {
                // If the first term has an MF, we assume it's an input variable
                // In our logic, output variables might have empty terms but registered centers
                // Wait, our registerOutputTermCenter adds to a separate map.
                // Let's check if it's an input variable by checking if it has ANY term with MF.
                facts[name] = view.promptForFact(name);
            }
        }

        auto results = engine.infer(kb, facts);
        view.displayResults(results);
    }
};
