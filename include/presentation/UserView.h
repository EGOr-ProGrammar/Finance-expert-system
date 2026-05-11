#pragma once
#include <iostream>
#include <string>
#include <map>

class UserView {
public:
    void showHeader() const {
        std::cout << "--- Financial Fuzzy Expert System (User Mode) ---" << std::endl;
    }

    void showMessage(const std::string& msg) const {
        std::cout << msg << std::endl;
    }

    double promptForFact(const std::string& varName) const {
        double val;
        std::cout << "Enter value for [" << varName << "]: ";
        std::cin >> val;
        return val;
    }

    void displayResults(const std::map<std::string, double>& results) const {
        std::cout << "\n--- Inference Results ---" << std::endl;
        if (results.empty()) {
            std::cout << "Warning: No rules were activated." << std::endl;
        } else {
            for (const auto& [varName, value] : results) {
                std::cout << "Output [" << varName << "]: " << value << std::endl;
            }
        }
    }
};
