#pragma once
#include "Building.hpp"
#include "UpgradeId.hpp"
#include <array>
#include <string>
#include <string_view>

class Upgrade
{
public:
  Upgrade (std::string_view name, std::string_view desc);
  bool isUnlocked () const;
  void unlock ();
  std::string_view getName () const;
  std::string_view getDescription () const;
  std::list<std::pair<RessourceType, double> > getCost () const;

  static constexpr std::array<UpgradeID, 3> upgradeIDs
      = { UpgradeID::FocusingForInsight, UpgradeID::Manufacturing,
          UpgradeID::Writing };

private:
  bool bought = false;
  const std::string_view name;
  const std::string_view description;
  std::list<std::pair<RessourceType, double> > cost;
};
