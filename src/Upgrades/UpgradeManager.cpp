#include "UpgradeManager.hpp"
#include "Ressource.hpp"
#include "Upgrade.hpp"
#include "UpgradeFactory.hpp"
#include "UpgradeId.hpp"
#include <string_view>

UpgradeManager::UpgradeManager ()
{
  for (const auto &id : Upgrade::upgradeIDs)
    {
      upgrades.emplace (id, UpgradeFactory::createUpgrade (id));
    }
}

bool
UpgradeManager::isUnlocked (UpgradeID id) const
{
  return upgrades.at (id).isUnlocked ();
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