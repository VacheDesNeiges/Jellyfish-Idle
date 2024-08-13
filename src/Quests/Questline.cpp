#include "Questline.hpp"
#include "GameIDsTypes.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <utility>
#include <vector>

Questline::Questline(const nlohmann::json &json)
{
    try
    {
        quests.reserve(json.at("Quests").size());
        for (const auto &quest : json.at("Quests"))
        {
            quests.emplace_back(quest);
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing a questline :\n" << e.what() << '\n';
        abort();
    }
}

std::string Questline::getCurrentQuestText() const
{
    return quests.at(currentQuest).getDialogue();
}

std::vector<std::pair<RessourceType, double>> Questline::
    getCurrentQuestRequirements() const
{
    return quests.at(currentQuest).getRequestedRessources();
}