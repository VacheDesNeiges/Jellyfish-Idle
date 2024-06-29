#include "CallThunder.hpp"

#include "InsightAbility.hpp"
#include "RessourceType.hpp"

#include <string>

CallThunder::CallThunder ()
{
  using namespace RessourcesAlias;
  name = "Lightning";
  castingCost = { { INSIGHT, 100 }, { SAND, 100 } };
  ressourcesGained = { { GLASS, 10 } };
}

std::string
CallThunder::getDescription ()
{
  return "Call a lightning to melt some sand into glass";
}