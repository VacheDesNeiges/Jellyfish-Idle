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

private:
  std::map<AbilityType, InsightAbility> abilities;
};
