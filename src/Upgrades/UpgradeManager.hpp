#pragma once

#include "GameDataAccess.hpp"
#include "Ressource.hpp"
#include "Upgrade.hpp"
#include "UpgradeId.hpp"
#include <map>

class UpgradeManager : public GameDataAccess
{
public:
  UpgradeManager ();
  void buy (UpgradeID);
  bool isUnlocked (UpgradeID) const;
  std::string_view getName (UpgradeID) const;
  std::string_view getDescription (UpgradeID) const;

  std::list<std::pair<RessourceType, double> > getCost (UpgradeID) const;

private:
  std::map<UpgradeID, Upgrade> upgrades;
};