#include "UpgradeManager.hpp"
#include "Ressource.hpp"
#include "Upgrade.hpp"
#include "UpgradeDataView.hpp"
#include "UpgradeFactory.hpp"
#include "UpgradeId.hpp"
#include <string_view>
#include <utility>
#include <vector>

UpgradeManager::UpgradeManager ()
{
  upgrades.reserve (UpgradesTypes.size ());
  upgradesConditions.reserve (UpgradesTypes.size ());
  for (const auto &id : UpgradesTypes)
    {
      upgrades.try_emplace (id, UpgradeFactory::createUpgrade (id));
    }

  using enum UpgradeID;
  upgradesConditions = {
    { Focusing, [] () { return true; } },

    { AbilityLightning,
      [this] () { return upgrades[Focusing].isUnlocked (); } },

    { Telekinesis, [this] () { return upgrades[Focusing].isUnlocked (); } },

    { AdvancedTelekinesis,
      [this] () { return upgrades[Telekinesis].isUnlocked (); } },

    { Writing,
      [this] () { return upgrades[AdvancedTelekinesis].isUnlocked (); } }
  };
}

bool
UpgradeManager::isBought (UpgradeID id) const
{
  return upgrades.at (id).isUnlocked ();
}

bool
UpgradeManager::isAvailableForBuying (UpgradeID id) const
{
  return (!(upgrades.at (id).isUnlocked ()) && upgradesConditions.at (id));
}

std::string_view
UpgradeManager::getName (UpgradeID id) const
{
  return upgrades.at (id).getName ();
}

std::string_view
UpgradeManager::getDescription (UpgradeID id) const
{
  return upgrades.at (id).getDescription ();
}

std::vector<std::pair<RessourceType, double> >
UpgradeManager::getCost (UpgradeID id) const
{
  return upgrades.at (id).getCost ();
}

void
UpgradeManager::buy (UpgradeID id)
{
  upgrades[id].unlock ();
}

std::vector<std::pair<UpgradeID, bool> >
UpgradeManager::getData () const
{
  std::vector<std::pair<UpgradeID, bool> > data;
  data.reserve (UpgradesTypes.size ());
  for (const auto &[id, upgrade] : upgrades)
    {
      data.emplace_back (id, upgrade.isUnlocked ());
    }
  return data;
}

void
UpgradeManager::loadData (const std::vector<std::pair<UpgradeID, bool> > &data)
{
  for (const auto &[id, val] : data)
    {
      if (val)
        {
          upgrades[id].unlock ();
        }
    }
}