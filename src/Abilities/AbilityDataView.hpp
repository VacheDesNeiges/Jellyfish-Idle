#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <vector>

class AbilityManager;
class RessourceManager;

class AbilityDataView
{
public:
  explicit AbilityDataView (std::shared_ptr<AbilityManager>,
                            std::shared_ptr<RessourceManager>);

  std::string getAbilityName (AbilityType) const;
  std::string getAbilityDescription (AbilityType) const;
  std::vector<std::pair<RessourceType, double> > getCost (AbilityType) const;
  bool isUsable (AbilityType) const;

private:
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<RessourceManager> ressources;
};