#pragma once

#include "InsightAbility.hpp"
#include "Ressource.hpp"
#include <map>

class AbilityManager
{
public:
  AbilityManager ();
  void useAbility (AbilityType);
  std::vector<std::pair<RessourceType, double> > getAbilityCost ();
  std::string getAbilityDescription (AbilityType);

private:
  std::map<AbilityType, std::unique_ptr<InsightAbility> > abilities;
};
