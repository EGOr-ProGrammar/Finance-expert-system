#pragma once
#include <memory>
#include <iostream>
#include "core/KnowledgeBase.h"
#include "presentation/ExpertView.h"
#include "json/KnowledgeBaseLoader.h"
#include "json/KnowledgeBaseSaver.h"
#include "membership/GaussianFunction.h"
#include "membership/TrapezoidalFunction.h"

class ExpertController {
private:
    KnowledgeBase kb;
    ExpertView view;
    std::string kbPath;

public:
    ExpertController(std::string path) : kbPath(std::move(path)) {}

    void run() {
        try {
            KnowledgeBaseLoader::load(kbPath, kb);
            view.showMessage("Knowledge base loaded from " + kbPath);
        } catch (...) {
            view.showMessage("Starting with a new knowledge base.");
        }

        int choice = -1;
        while (choice != 0) {
            view.showMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: view.displayKB(kb); break;
                case 2: addInputVariable(); break;
                case 3: addOutputVariable(); break;
                case 4: addRule(); break;
                case 5:
                    KnowledgeBaseSaver::save(kbPath, kb);
                    view.showMessage("Saved to " + kbPath);
                    return;
                case 0: break;
                default: view.showMessage("Invalid choice.");
            }
        }
    }

private:
    void addInputVariable() {
        std::string name = view.promptString("Variable name: ");
        LinguisticVariable var(name);
        int termCount = view.promptInt("Number of terms: ");
        for (int i = 0; i < termCount; ++i) {
            std::string tName = view.promptString("Term name: ");
            int type = view.promptInt("Type (1: Gaussian, 2: Trapezoidal): ");
            if (type == 1) {
                double c = view.promptDouble("Center (c): ");
                double s = view.promptDouble("Sigma (s): ");
                var.addTerm(tName, std::make_shared<GaussianFunction>(c, s));
            } else {
                double c = view.promptDouble("Center (c): ");
                double t = view.promptDouble("Top width (t): ");
                double s = view.promptDouble("Slope (s): ");
                var.addTerm(tName, std::make_shared<TrapezoidalFunction>(c, t, s));
            }
        }
        kb.addVariable(var);
    }

    void addOutputVariable() {
        std::string name = view.promptString("Output Variable name: ");
        LinguisticVariable var(name); // Wrapper for the name
        int termCount = view.promptInt("Number of terms: ");
        for (int i = 0; i < termCount; ++i) {
            std::string tName = view.promptString("Term name: ");
            double center = view.promptDouble("Center value: ");
            kb.registerOutputTermCenter(name, tName, center);
        }
        kb.addVariable(var);
    }

    void addRule() {
        std::string outVar = view.promptString("Output variable: ");
        std::string outTerm = view.promptString("Output term: ");
        Rule rule(outVar, outTerm);
        int condCount = view.promptInt("Number of conditions: ");
        for (int i = 0; i < condCount; ++i) {
            std::string v = view.promptString("If Variable: ");
            std::string t = view.promptString("Is Term: ");
            rule.addCondition(v, t);
        }
        kb.addRule(rule);
    }
};
