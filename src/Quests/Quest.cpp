#include "Quest.hpp"
#include "GameIDsTypes.hpp"
#include <vector>

Quest::Quest (const nlohmann::json &json)
{
  dialogue = json.at ("Text");
  requestedRessources.reserve (json.at ("CompletionRequirements").size ());
  for (const auto &requirements : json.at ("CompletionRequirements"))
    {
      requestedRessources.emplace_back (
          RessourceType (requirements.at ("RessourceID")),
          requirements.at ("Quantity"));
    }
}

bool
Quest::isCompleted () const
{
  return completed;
}

std::string
Quest::getDialogue () const
{
  return dialogue;
}

std::vector<std::pair<RessourceType, double> >
Quest::getRequestedRessources () const
{
  return requestedRessources;
}
