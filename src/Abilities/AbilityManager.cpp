#include "AbilityManager.hpp"

#include "InsightAbility.hpp"
#include "Ressource.hpp"
#include "RessourceDataView.hpp"

AbilityManager::AbilityManager ()
{
  abilities.reserve (InsightAbility::AbilitiesTypes.size ());
  abilities[AbilityType::AbilityLightning]
      = AbilityFactory::createAbilityInstance (AbilityType::AbilityLightning);
}

bool
AbilityManager::isUsable (AbilityType t)
{
  bool buyable = true;
  for (const auto &[ressource, cost] : abilities[t]->getCost ())
    {

      if (!buyable)
        continue;

      if (ressourcesView ()->getRessourceQuantity (ressource) < cost)
        {
          buyable = false;
        }
    }
  return buyable;
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
