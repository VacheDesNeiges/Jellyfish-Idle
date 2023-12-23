#pragma once
#include "Building.hpp"
#include "UpgradeId.hpp"
#include <array>
#include <string>

class Upgrade
{
public:
  std::string getDescription ();

  static constexpr std::array<UpgradeID, 3> upgradeIDs
      = { UpgradeID::CanalizingInsight, UpgradeID::Manufacturing,
          UpgradeID::Writing };

private:
  bool bought = false;
  std::string description;
  std::list<std::pair<RessourceType, double> > cost;
};
