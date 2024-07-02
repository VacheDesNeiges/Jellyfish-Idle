#include "SaveSystem.hpp"

#include "AchievementIDs.hpp"
#include "AquaCulture.hpp"
#include "Building.hpp"
#include "CraftingRecipe.hpp"
#include "DepthSystem.hpp"
#include "JellyfishManager.hpp"
#include "RecipeID.hpp"
#include "Ressource.hpp"
#include "UpgradeDataView.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

void
SaveSystem::save (const SaveData &data)
{
  nlohmann::json j;
  for (const auto &[type, quant] : data.buildings)
    {
      j["Building"]
          += { { "id", static_cast<int> (type) }, { "Quantity", quant } };
    }

  for (const auto &[idAch, isUnlocked] : data.achievements)
    {
      j["Achievement"] += { { "id", static_cast<unsigned> (idAch) },
                            { "Unlocked", isUnlocked } };
    }

  for (const auto &[idRes, quant] : data.ressources)
    {
      j["Ressource"]
          += { { "id", static_cast<int> (idRes) }, { "Quantity", quant } };
    }

  j["Jellies"] += {
    { "num", data.jellies.numJellies },
    { "numMax", data.jellies.maxNumJellies },
    { "numJobNone", data.jellies.numJobNone },
    { "numJobExplore", data.jellies.numJobExploreTheDepths },
    { "numJobMining", data.jellies.numJobMining },
    { "numJobFocusing", data.jellies.numJobFocusing },
    { "numJobCrafting", data.jellies.numJobCrafting },
  };

  j["Depth"] += {
    { "currentDepth", data.depth.currentDepth },
    { "currentProg", data.depth.currentProg },
  };

  for (const auto &[id, val] : data.upgrades)
    {
      j["Upgrade"] += {
        { "id", static_cast<unsigned> (id) },
        { "Bought", val },
      };
    }

  for (const auto &[id, craftData] : data.crafts)
    {
      j["Craft"] += {
        { "id", static_cast<unsigned> (id) },
        { "Workers", craftData.numAssignedWorkers },
        { "Done", craftData.craftDone },
        { "Ongoing", craftData.craftOngoing },
        { "RemainingTicks", craftData.remainingTicksToCraft },
        { "Level", craftData.lvl },
        { "CurrentProg", craftData.progressNeeded },
      };
    }

  for (const auto &[id, cultureData] : data.cultures)
    {
      j["Culture"] += {
        { "id", static_cast<unsigned> (id) },
        { "Fields", cultureData.fieldCount },
        { "Ongoing", cultureData.craftOngoing },
      };
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

  result.buildings.reserve (
      Building::getBuildingTypes ().size ()); // FIXME use size in json
  for (const auto &d : data["Building"])
    {
      result.buildings.emplace_back (
          static_cast<BuildingType> (d["id"].get<int> ()),
          d["Quantity"].get<unsigned> ());
    }

  result.achievements.reserve (allAchievementsIDs.size ());
  for (const auto &d : data["Achievement"])
    {
      result.achievements.emplace_back (
          static_cast<AchievementIDs> (d["id"].get<unsigned> ()),
          d["Unlocked"].get<bool> ());
    }

  result.ressources.reserve (
      Ressource::getRessourcesTypes ().size ()
      + Ressource::getCraftableRessourcesTypes ().size ()
      + Ressource::getRareRessourcesTypes ().size ());
  for (const auto &d : data["Ressource"])
    {
      result.ressources.emplace_back (
          static_cast<RessourceType> (d["id"].get<int> ()),
          d["Quantity"].get<double> ());
    }

  result.jellies.numJellies = data["Jellies"][0]["num"].get<unsigned> ();
  result.jellies.maxNumJellies = data["Jellies"][0]["numMax"].get<unsigned> ();

  result.jellies.numJobNone
      = data["Jellies"][0]["numJobNone"].get<unsigned> ();
  result.jellies.numJobExploreTheDepths
      = data["Jellies"][0]["numJobExplore"].get<unsigned> ();
  result.jellies.numJobMining
      = data["Jellies"][0]["numJobMining"].get<unsigned> ();
  result.jellies.numJobFocusing
      = data["Jellies"][0]["numJobFocusing"].get<unsigned> ();
  result.jellies.numJobCrafting
      = data["Jellies"][0]["numJobCrafting"].get<unsigned> ();

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

  result.crafts.reserve (CraftingRecipe::RecipeTypes.size ());
  for (const auto &c : data["Craft"])
    {
      result.crafts.emplace_back (
          static_cast<RecipeID> (c["id"].get<unsigned> ()),
          RecipeSaveData{
              c["Level"].get<unsigned> (),
              c["CurrentProg"].get<double> (),
              0,
              c["Ongoing"].get<bool> (),
              c["Done"].get<bool> (),
              c["RemainingTicks"].get<unsigned> (),
              c["Workers"].get<unsigned> (),
          });
    }

  result.cultures.reserve (AquaCulture::CultureTypes.size ());
  for (const auto &c : data["Culture"])
    {
      result.cultures.emplace_back (
          static_cast<AquaCultureID> (c["id"].get<unsigned> ()),
          CultureData{
              c["Ongoing"].get<bool> (),
              c["Fields"].get<unsigned> (),
          });
    }

  return result;
}