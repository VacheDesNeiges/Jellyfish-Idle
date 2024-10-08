#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <span>
#include <vector>

class AbilityManager;
class RessourceManager;

class AbilityDataView
{
  public:
    explicit AbilityDataView(const std::shared_ptr<AbilityManager> &,
                             const std::shared_ptr<RessourceManager> &);

    std::string getAbilityName(AbilityType) const;
    std::string getAbilityDescription(AbilityType) const;
    std::vector<std::pair<RessourceType, double>> getCost(AbilityType) const;
    std::span<const AbilityType> getAbilityTypes() const;
    bool isUsable(AbilityType) const;

  private:
    std::shared_ptr<const AbilityManager> abilities;
    std::shared_ptr<const RessourceManager> ressources;
};
