#include "CallThunder.hpp"
#include "InsightAbility.hpp"
#include "Ressource.hpp"
#include <string>
#include <utility>

CallThunder::CallThunder ()
{
  name = "Call Thunder";
  castingCost
      = { { RessourceType::Insight, 100 }, { RessourceType::Sand, 100 } };
  ressourcesGained = { { RessourceType::Glass, 10 } };
}

std::string
CallThunder::getDescription ()
{
  return "Call the thunder to melt some sand into glass";
}