#include "Quest.hpp"
#include "GameIDsTypes.hpp"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <vector>

Quest::Quest(const nlohmann::json &json)
{
    try
    {
        dialogue = json.at("Text");
        requestedRessources.reserve(json.at("CompletionRequirements").size());
        for (const auto &requirements : json.at("CompletionRequirements"))
        {
            requestedRessources.emplace_back(
                RessourceType(requirements.at("RessourceID")),
                requirements.at("Quantity"));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "error while parsing a quest :\n" << e.what() << '\n';
        abort();
    }
}

bool Quest::isCompleted() const
{
    return completed;
}

std::string Quest::getDialogue() const
{
    return dialogue;
}

std::vector<std::pair<RessourceType, double>> Quest::getRequestedRessources()
    const
{
    return requestedRessources;
}
