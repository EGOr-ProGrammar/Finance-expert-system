#pragma once
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "core/KnowledgeBase.h"

using json = nlohmann::json;

class KnowledgeBaseSaver {
public:
    static void save(const std::string& filepath, const KnowledgeBase& kb) {
        json j;
        
        // 1. Serialize variables
        j["variables"] = json::array();
        for (const auto& [varName, var] : kb.getVariables()) {
            json varJson;
            varJson["name"] = varName;
            varJson["terms"] = json::array();
            
            // Check if it's an output variable with centers
            auto centers = kb.getTermCenters(varName);
            
            // Collect all terms (both with MF and with centers)
            // Note: In our current logic, a variable can have EITHER MF terms OR center terms
            // or both, but the loader treats them separately.
            
            // First, add terms with membership functions
            for (const auto& [termName, mf] : var.getTerms()) {
                json termJson = mf->serialize();
                termJson["name"] = termName;
                varJson["terms"].push_back(termJson);
            }
            
            // Then, add terms with centers (if any)
            if (centers) {
                for (const auto& [termName, center] : *centers) {
                    // Check if we already added this term (shouldn't happen in a clean KB)
                    bool exists = false;
                    for (const auto& t : varJson["terms"]) {
                        if (t["name"] == termName) { exists = true; break; }
                    }
                    if (!exists) {
                        varJson["terms"].push_back({
                            {"name", termName},
                            {"center", center}
                        });
                    }
                }
            }
            
            j["variables"].push_back(varJson);
        }
        
        // 2. Serialize rules
        j["rules"] = json::array();
        for (const auto& rule : kb.getRules()) {
            json ruleJson;
            ruleJson["output"] = {
                {"variable", rule.getOutputVariable()},
                {"term", rule.getOutputTerm()}
            };
            
            ruleJson["conditions"] = json::array();
            for (const auto& cond : rule.getConditions()) {
                ruleJson["conditions"].push_back({
                    {"variable", cond.variableName},
                    {"term", cond.termName}
                });
            }
            
            j["rules"].push_back(ruleJson);
        }
        
        std::ofstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for saving: " + filepath);
        }
        file << j.dump(2);
    }
};
