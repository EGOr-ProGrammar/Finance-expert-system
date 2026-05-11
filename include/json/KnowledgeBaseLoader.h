#pragma once
#include <fstream>
#include <memory>
#include <stdexcept>
#include "json.hpp"
#include "core/KnowledgeBase.h"
#include "membership/GaussianFunction.h"
#include "membership/GeneralizedGaussianFunction.h"
#include "membership/TrapezoidalFunction.h"

using json = nlohmann::json;

class KnowledgeBaseLoader
{
public:
    static void load(const std::string &filepath, KnowledgeBase &kb)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open knowledge base file: " + filepath);
        }

        json j;
        file >> j;

        for (const auto &varJson : j.at("variables"))
        {
            LinguisticVariable lv(varJson.at("name").get<std::string>());

            for (const auto &termJson : varJson.at("terms"))
            {
                std::string termName = termJson.at("name").get<std::string>();

                if (termJson.contains("center"))
                {
                    kb.registerOutputTermCenter(
                        lv.getName(),
                        termName,
                        termJson.at("center").get<double>());
                    continue;
                }

                std::string type = termJson.at("type").get<std::string>();
                const auto &params = termJson.at("params");

                std::shared_ptr<IMembershipFunction> mf = nullptr;

                if (type == "gaussian")
                {
                    mf = std::make_shared<GaussianFunction>(
                        params.at("c").get<double>(),
                        params.at("sigma").get<double>());
                }
                else if (type == "generalized_gaussian")
                {
                    mf = std::make_shared<GeneralizedGaussianFunction>(
                        params.at("c").get<double>(),
                        params.at("sigma").get<double>(),
                        params.at("b").get<double>());
                }
                else if (type == "trapezoidal")
                {
                    mf = std::make_shared<TrapezoidalFunction>(
                        params.at("c").get<double>(),
                        params.at("t").get<double>(),
                        params.at("s").get<double>());
                }
                else
                {
                    throw std::runtime_error("Unknown membership function type: " + type);
                }

                lv.addTerm(termName, mf);
            }
            kb.addVariable(lv);
        }

        for (const auto &ruleJson : j.at("rules"))
        {
            std::string outVar = ruleJson.at("output").at("variable").get<std::string>();
            std::string outTerm = ruleJson.at("output").at("term").get<std::string>();

            Rule rule(outVar, outTerm);

            for (const auto &condJson : ruleJson.at("conditions"))
            {
                rule.addCondition(
                    condJson.at("variable").get<std::string>(),
                    condJson.at("term").get<std::string>());
            }
            kb.addRule(rule);
        }
    }
};
