#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "InsightAbility.hpp"
#include <unordered_map>

class AbilityManager : public GameDataAccess {
public:
  AbilityManager();
  bool isUsable(AbilityType) const;
  std::vector<std::pair<RessourceType, double>>
      getAbilityCost(AbilityType) const;
  std::vector<std::pair<RessourceType, double>>
      getProduction(AbilityType) const;
  std::string getAbilityDescription(AbilityType) const;
  std::string getAbilityName(AbilityType) const;

  std::span<const AbilityType> getAllAbilityTypes() const;

private:
  std::vector<AbilityType> abilitiesTypes;
  std::unordered_map<AbilityType, InsightAbility> abilities;
};
