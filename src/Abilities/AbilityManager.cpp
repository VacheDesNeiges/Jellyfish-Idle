#include "AbilityManager.hpp"
#include "CallThunder.hpp"
#include "InsightAbility.hpp"
#include "Ressource.hpp"

AbilityManager::AbilityManager ()
{
  abilities[AbilityType::CallThunder]
      = AbilityFactory::createAbilityInstance (AbilityType::CallThunder);
}

std::vector<std::pair<RessourceType, double> >
AbilityManager::getAbilityCost (AbilityType t)
{
  return abilities[t]->getCost ();
}

std::vector<std::pair<RessourceType, double> >
AbilityManager::getProduction (AbilityType t)
{
  return abilities[t]->getProduction ();
}

std::string
AbilityManager::getAbilityName (AbilityType t)
{
  return abilities[t]->getName ();
}

std::string
AbilityManager::getAbilityDescription (AbilityType t)
{
  return abilities[t]->getDescription ();
}
