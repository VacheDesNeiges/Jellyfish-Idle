#include "AbilityManager.hpp"
#include "CallThunder.hpp"
#include "InsightAbility.hpp"
#include "Ressource.hpp"

AbilityManager::AbilityManager ()
{
  abilities[AbilityType::CallThunder]
      = AbilityFactory::createAbilityInstance (AbilityType::CallThunder);
}

void
AbilityManager::useAbility (AbilityType t)
{
}

std::vector<std::pair<RessourceType, double> >
AbilityManager::getAbilityCost ()
{
  return { {} };
}

std::string
AbilityManager::getAbilityDescription (AbilityType t)
{
  return abilities[t]->getDescription ();
}
