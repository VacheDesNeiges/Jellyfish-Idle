#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "SaveAndLoadable.hpp"
#include "Upgrade.hpp"
#include <unordered_map>

class UpgradeManager
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<UpgradeID, bool>>>
{
  public:
    UpgradeManager();
    virtual ~UpgradeManager() = default;
    void buy(UpgradeID);
    bool isAvailableForBuying(UpgradeID) const;
    bool isBought(UpgradeID) const;
    std::string_view getName(UpgradeID) const;
    std::string_view getDescription(UpgradeID) const;
    std::vector<std::pair<RessourceType, double>> getCost(UpgradeID) const;

    std::vector<std::pair<UpgradeID, bool>> getData() const override;
    void loadData(const std::vector<std::pair<UpgradeID, bool>> &data) override;

    std::span<const UpgradeID> getUpgradesTypes() const;

  private:
    std::vector<UpgradeID> upgradeTypes;
    std::unordered_map<UpgradeID, Upgrade> upgrades;
};
