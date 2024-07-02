#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "InsightAbility.hpp"

#include <unordered_map>

class AbilityManager : public GameDataAccess
{
public:
  AbilityManager ();
  bool isUsable (AbilityType);
  std::vector<std::pair<RessourceType, double> > getAbilityCost (AbilityType);
  std::vector<std::pair<RessourceType, double> > getProduction (AbilityType);
  std::string getAbilityDescription (AbilityType);
  std::string getAbilityName (AbilityType);

private:
  std::unordered_map<AbilityType, std::unique_ptr<InsightAbility> > abilities;
};
