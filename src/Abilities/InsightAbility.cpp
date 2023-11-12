#include "InsightAbility.hpp"
#include "CallThunder.hpp"
#include <memory>

std::unique_ptr<InsightAbility>
AbilityFactory::createAbilityInstance (AbilityType t)
{
  switch (t)
    {
    case AbilityType::CallThunder:
      return std::make_unique<CallThunder> ();

    default:
      return nullptr;
    }
}

std::vector<std::pair<RessourceType, double> >
InsightAbility::getCost () const
{
  return castingCost;
}

std::vector<std::pair<RessourceType, double> >
InsightAbility::getProduction () const
{
  return ressourcesGained;
}

std::string
InsightAbility::getName () const
{
  return name;
}