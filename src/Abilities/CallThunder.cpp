#include "CallThunder.hpp"
#include "InsightAbility.hpp"
#include "Ressource.hpp"
#include <string>
#include <utility>

CallThunder::CallThunder ()
{
  using enum RessourceType;
  name = "Call Thunder";
  castingCost = { { Insight, 100 }, { Sand, 100 } };
  ressourcesGained = { { Glass, 10 } };
}

std::string
CallThunder::getDescription ()
{
  return "Call the thunder to melt some sand into glass";
}