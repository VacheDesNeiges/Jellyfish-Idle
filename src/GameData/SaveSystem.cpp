#include "SaveSystem.hpp"
#include "AchievementIDs.hpp"
#include "Building.hpp"
#include "DepthSystem.hpp"
#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include "UpgradeDataView.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

void
SaveSystem::save (SaveData data)
{
  nlohmann::json j;
  for (const auto &[type, quant] : data.buildings)
    {
      j["Building"]
          += { { "id", static_cast<unsigned> (type) }, { "Quantity", quant } };
    }

  for (const auto &[idAch, isUnlocked] : data.achievements)
    {
      j["Achievement"] += { { "id", static_cast<unsigned> (idAch) },
                            { "Unlocked", isUnlocked } };
    }

  for (const auto &[idRes, quant] : data.ressources)
    {
      j["Ressource"] += { { "id", static_cast<unsigned> (idRes) },
                          { "Quantity", quant } };
    }

  j["Jellies"] += { { "num", data.jellies.numJellies },
                    { "numMax", data.jellies.maxNumJellies },
                    { "numJobNone", data.jellies.numJobNone },
                    { "numJobGatherFood", data.jellies.numJobGatheringFood },
                    { "numJobExplore", data.jellies.numJobExploreTheDepths },
                    { "numJobGatherSand", data.jellies.numJobGatheringSand },
                    { "numJobMining", data.jellies.numJobMining },
                    { "numJobFocusing", data.jellies.numJobFocusing } };

  j["Depth"] += { { "currentDepth", data.depth.currentDepth },
                  { "currentProg", data.depth.currentProg } };

  for (const auto &[id, val] : data.upgrades)
    {
      j["Upgrade"]
          += { { "id", static_cast<unsigned> (id) }, { "Bought", val } };
    }

  std::ofstream file (saveFileName);
  file << j;
}

SaveData
SaveSystem::loadFromFile (std::string path)
{
  SaveData result;
  path += "/" + saveFileName;

  std::ifstream f (path);
  nlohmann::json data = nlohmann::json::parse (f);

  result.buildings.reserve (Building::BuildingTypes.size ());
  for (const auto &d : data["Building"])
    {
      result.buildings.emplace_back (
          static_cast<BuildingType> (d["id"].get<unsigned> ()),
          d["Quantity"].get<unsigned> ());
    }

  result.achievements.reserve (allAchievementsIDs.size ());
  for (const auto &d : data["Achievement"])
    {
      result.achievements.emplace_back (
          static_cast<AchievementIDs> (d["id"].get<unsigned> ()),
          d["Unlocked"].get<bool> ());
    }

  result.ressources.reserve (Ressource::RessourceTypes.size ()
                             + Ressource::CraftableRessourceTypes.size ());
  for (const auto &d : data["Ressource"])
    {
      result.ressources.emplace_back (
          static_cast<RessourceType> (d["id"].get<unsigned> ()),
          d["Quantity"].get<double> ());
    }

  result.jellies.numJellies = data["Jellies"][0]["num"].get<unsigned> ();
  result.jellies.maxNumJellies = data["Jellies"][0]["numMax"].get<unsigned> ();

  result.jellies.numJobNone
      = data["Jellies"][0]["numJobNone"].get<unsigned> ();
  result.jellies.numJobExploreTheDepths
      = data["Jellies"][0]["numJobExplore"].get<unsigned> ();
  result.jellies.numJobGatheringFood
      = data["Jellies"][0]["numJobGatherFood"].get<unsigned> ();
  result.jellies.numJobGatheringSand
      = data["Jellies"][0]["numJobGatherSand"].get<unsigned> ();
  result.jellies.numJobMining
      = data["Jellies"][0]["numJobMining"].get<unsigned> ();
  result.jellies.numJobFocusing
      = data["Jellies"][0]["numJobFocusing"].get<unsigned> ();

  result.depth.currentDepth
      = data["Depth"][0]["currentDepth"].get<unsigned> ();
  result.depth.currentProg = data["Depth"][0]["currentProg"].get<float> ();

  result.upgrades.reserve (UpgradeManager::UpgradesTypes.size ());
  for (const auto &d : data["Upgrade"])
    {
      result.upgrades.emplace_back (
          static_cast<UpgradeID> (d["id"].get<unsigned> ()),
          d["Bought"].get<bool> ());
    }

  return result;
}