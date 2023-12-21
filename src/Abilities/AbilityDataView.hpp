#pragma once
#include "AbilityManager.hpp"
#include "RessourceManager.hpp"
#include <memory>
class AbilityDataView
{
public:
  explicit AbilityDataView (std::shared_ptr<AbilityManager>,
                            std::shared_ptr<RessourceManager>);

  std::string getAbilityName (AbilityType) const;
  std::string getAbilityDescription (AbilityType) const;
  bool isUsable (AbilityType) const;

private:
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<RessourceManager> ressources;
};