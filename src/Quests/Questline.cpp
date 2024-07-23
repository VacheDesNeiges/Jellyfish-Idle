#include "Questline.hpp"
#include <nlohmann/json.hpp>

Questline::Questline (const nlohmann::json &json)
{
  quests.reserve (json.at ("Quests").size ());
  for (const auto &quest : json.at ("Quests"))
    {
      quests.emplace_back (quest);
    }
}