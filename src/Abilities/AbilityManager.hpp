#pragma once

#include "InsightAbility.hpp"
#include "Ressource.hpp"
#include <map>

class AbilityManager
{
public:
  AbilityManager ();
  std::vector<std::pair<RessourceType, double> > getAbilityCost (AbilityType);
  std::vector<std::pair<RessourceType, double> > getProduction (AbilityType);
  std::string getAbilityDescription (AbilityType);
  std::string getAbilityName (AbilityType);

private:
  std::map<AbilityType, std::unique_ptr<InsightAbility> > abilities;
};
