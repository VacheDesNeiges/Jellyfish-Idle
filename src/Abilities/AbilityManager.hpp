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

  std::span<const AbilityType> getAllAbilityTypes () const;

private:
  std::vector<AbilityType> abilitiesTypes;
  std::unordered_map<AbilityType, InsightAbility> abilities;
};
