#include "CallThunder.hpp"

#include "InsightAbility.hpp"
#include "Ressource.hpp"

#include <string>

CallThunder::CallThunder ()
{
  using enum RessourceType;
  name = "Lightning";
  castingCost = { { Insight, 100 }, { Sand, 100 } };
  ressourcesGained = { { Glass, 10 } };
}

std::string
CallThunder::getDescription ()
{
  return "Call a lightning to melt some sand into glass";
}