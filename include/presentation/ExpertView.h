#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "core/KnowledgeBase.h"

class ExpertView {
public:
    void showMessage(const std::string& msg) const {
        std::cout << msg << std::endl;
    }

    void showMenu() const {
        std::cout << "\n--- Expert Mode: Knowledge Base Management ---" << std::endl;
        std::cout << "1. View Knowledge Base" << std::endl;
        std::cout << "2. Add Input Variable" << std::endl;
        std::cout << "3. Add Output Variable (with centers)" << std::endl;
        std::cout << "4. Add Rule" << std::endl;
        std::cout << "5. Save and Exit" << std::endl;
        std::cout << "0. Exit without saving" << std::endl;
        std::cout << "Choice: ";
    }

    void displayKB(const KnowledgeBase& kb) const {
        std::cout << "\n--- Current Knowledge Base ---" << std::endl;
        std::cout << "Variables:" << std::endl;
        for (const auto& [name, var] : kb.getVariables()) {
            std::cout << "  - " << name << " (" << var.getTerms().size() << " terms)" << std::endl;
            for (const auto& [tName, mf] : var.getTerms()) {
                std::cout << "    * " << tName << " (MF type: " << mf->serialize()["type"] << ")" << std::endl;
            }
            auto centers = kb.getTermCenters(name);
            if (centers) {
                for (const auto& [tName, val] : *centers) {
                    std::cout << "    * " << tName << " (Center: " << val << ")" << std::endl;
                }
            }
        }
        std::cout << "Rules: " << kb.getRules().size() << std::endl;
        int i = 1;
        for (const auto& rule : kb.getRules()) {
            std::cout << "  " << i++ << ". IF ";
            const auto& conds = rule.getConditions();
            for (size_t j = 0; j < conds.size(); ++j) {
                std::cout << conds[j].variableName << " IS " << conds[j].termName;
                if (j < conds.size() - 1) std::cout << " AND ";
            }
            std::cout << " THEN " << rule.getOutputVariable() << " IS " << rule.getOutputTerm() << std::endl;
        }
    }

    std::string promptString(const std::string& prompt) const {
        std::string s;
        std::cout << prompt;
        std::cin >> s;
        return s;
    }

    double promptDouble(const std::string& prompt) const {
        double d;
        std::cout << prompt;
        std::cin >> d;
        return d;
    }

    int promptInt(const std::string& prompt) const {
        int i;
        std::cout << prompt;
        std::cin >> i;
        return i;
    }
};
