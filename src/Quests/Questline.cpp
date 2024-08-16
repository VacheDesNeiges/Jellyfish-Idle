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
    if (currentQuest < quests.size())
        return quests.at(currentQuest).getDialogue();

    return "No more quest available";
}

std::vector<std::pair<RessourceType, double>> Questline::
    getCurrentQuestRequirements() const
{
    if (currentQuest < quests.size())
        return quests.at(currentQuest).getRequestedRessources();

    return {};
}

void Questline::completeQuest()
{
    quests.at(currentQuest).complete();
    currentQuest++;
}

void Questline::setCurrentQuest(unsigned newCurrentQuest)
{
    currentQuest = newCurrentQuest;
    for (size_t i = 0; i < currentQuest; i++)
    {
        quests.at(i).complete();
    }
}

unsigned Questline::getCurrentQuestIndex() const
{
    return currentQuest;
}

bool Questline::isComplete(unsigned i) const
{
    return quests.at(i).isComplete();
}
