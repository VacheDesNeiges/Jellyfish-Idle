#include "Questline.hpp"
#include "GameIDsTypes.hpp"
#include <nlohmann/json.hpp>
#include <utility>
#include <vector>

Questline::Questline (const nlohmann::json &json)
{
  quests.reserve (json.at ("Quests").size ());
  for (const auto &quest : json.at ("Quests"))
    {
      quests.emplace_back (quest);
    }
}

std::string
Questline::getCurrentQuestText () const
{
  return quests.at (currentQuest).getDialogue ();
}

std::vector<std::pair<RessourceType, double> >
Questline::getCurrentQuestRequirements () const
{
  return quests.at (currentQuest).getRequestedRessources ();
}