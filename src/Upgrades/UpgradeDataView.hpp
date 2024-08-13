#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <span>
#include <vector>

class UpgradeManager;
class RessourceManager;

class UpgradeDataView
{
  public:
    explicit UpgradeDataView(std::shared_ptr<UpgradeManager>,
                             std::shared_ptr<RessourceManager>);

    bool isAvailableForBuying(UpgradeID) const;
    bool isBuyable(UpgradeID) const;
    bool isBought(UpgradeID) const;
    std::string_view getName(UpgradeID) const;
    std::string_view getDescription(UpgradeID) const;
    std::vector<std::pair<RessourceType, double>> getCost(UpgradeID) const;
    std::span<const UpgradeID> getUpgradesTypes() const;

  private:
    std::shared_ptr<const UpgradeManager> upgrades;
    std::shared_ptr<const RessourceManager> ressources;
};