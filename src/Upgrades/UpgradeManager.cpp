#include "UpgradeManager.hpp"
#include "Ressource.hpp"
#include "Upgrade.hpp"
#include "UpgradeFactory.hpp"
#include "UpgradeId.hpp"
#include <string_view>

UpgradeManager::UpgradeManager ()
{
  for (const auto &id : UpgradesTypes)
    {
      upgrades.try_emplace (id, UpgradeFactory::createUpgrade (id));
    }
  using enum UpgradeID;
  upgradesConditions
      = { { FocusingForInsight, [] () { return true; } },

          { AbilityLightning,
            [this] () { return upgrades[FocusingForInsight].isUnlocked (); } },

          { Telekinesis,
            [this] () { return upgrades[FocusingForInsight].isUnlocked (); } },

          { Manufacturing,
            [this] () { return upgrades[Telekinesis].isUnlocked (); } } };
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

std::list<std::pair<RessourceType, double> >
UpgradeManager::getCost (UpgradeID id) const
{
  return upgrades.at (id).getCost ();
}

void
UpgradeManager::buy (UpgradeID id)
{
  upgrades[id].unlock ();
}
