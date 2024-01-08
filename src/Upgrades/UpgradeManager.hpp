#pragma once

#include "GameDataAccess.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"
#include "Upgrade.hpp"
#include "UpgradeId.hpp"
#include <functional>
#include <map>

class UpgradeManager
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<UpgradeID, bool> > >
{
public:
  UpgradeManager ();
  void buy (UpgradeID);
  bool isAvailableForBuying (UpgradeID) const;
  bool isBought (UpgradeID) const;
  std::string_view getName (UpgradeID) const;
  std::string_view getDescription (UpgradeID) const;
  std::vector<std::pair<RessourceType, double> > getCost (UpgradeID) const;

  std::vector<std::pair<UpgradeID, bool> > getData () const override;
  void loadData (const std::vector<std::pair<UpgradeID, bool> > &) override;

  static constexpr std::array<UpgradeID, 4> UpgradesTypes
      = { UpgradeID::FocusingForInsight, UpgradeID::Telekinesis,
          UpgradeID::AbilityLightning, UpgradeID::Manufacturing };

private:
  std::map<UpgradeID, Upgrade> upgrades;
  std::map<UpgradeID, std::function<bool ()> > upgradesConditions;
};