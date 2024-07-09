#include "UpgradeManager.hpp"

#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "UpgradeDataView.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

UpgradeManager::UpgradeManager ()
{
  const auto path = std::string (FilePaths::getPath ())
                    + std::string (FilePaths::UpgradesPath);
  std::ifstream fstream (path);

  try
    {
      auto upgradesJson = nlohmann::json::parse (fstream);
      upgrades.reserve (upgradesJson.at ("Upgrades").size ());
      upgradeTypes.reserve (upgradesJson.at ("Upgrades").size ());

      for (const auto &upgrade : upgradesJson["Upgrades"])
        {
          upgrades.try_emplace (UpgradeID (upgrade.at ("ID")), upgrade);
          upgradeTypes.push_back (UpgradeID (upgrade.at ("ID")));
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing upgrades :\n" << e.what () << "\n";
      abort ();
    }
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
  data.reserve (upgrades.size ());
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

std::span<const UpgradeID>
UpgradeManager::getUpgradesTypes () const
{
  return std::span (upgradeTypes);
}