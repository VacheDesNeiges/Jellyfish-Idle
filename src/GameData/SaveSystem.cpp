#include "SaveSystem.hpp"

#include "AquaCulture.hpp"
#include "CraftingRecipe.hpp"
#include "DepthSystem.hpp"
#include "GameIDsTypes.hpp"
#include "JellyfishManager.hpp"
#include "RecipeID.hpp"
#include "UpgradeDataView.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
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
      j["Achievement"] += { { "id", static_cast<int> (idAch) },
                            { "Unlocked", isUnlocked } };
    }

  for (const auto &[idRes, quant] : data.ressources)
    {
      j["Ressource"]
          += { { "id", static_cast<int> (idRes) }, { "Quantity", quant } };
    }

  j["Jellies"] = {
    { "num", data.jellies.numJellies },
    { "numMax", data.jellies.maxNumJellies },
    { "Jobs", nlohmann::json::array () },
  };

  try
    {
      for (const auto &[jobID, num] : data.jellies.jobNumbers)
        {
          j["Jellies"]["Jobs"].push_back (
              { { "id", jobID.value }, { "num", num } });
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while writting jellies :\n" << e.what () << '\n';
    }

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
        { "id", static_cast<int> (id) },
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

  nlohmann::json data;

  try
    {
      data = nlohmann::json::parse (f);
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing save with json::parse() :\n"
                << e.what () << '\n';
      abort ();
    }

  try
    {

      result.buildings.reserve (data.at ("Building").size ());
      for (const auto &d : data["Building"])
        {
          result.buildings.emplace_back (
              static_cast<BuildingType> (d["id"].get<int> ()),
              d["Quantity"].get<unsigned> ());
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing saved buildings :\n"
                << e.what () << '\n';
      abort ();
    }

  try
    {

      result.achievements.reserve (data.at ("Achievement").size ());
      for (const auto &d : data["Achievement"])
        {
          result.achievements.emplace_back (
              static_cast<AchievementIDs> (d["id"].get<int> ()),
              d["Unlocked"].get<bool> ());
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing saved buildings :\n"
                << e.what () << '\n';
      abort ();
    }

  try
    {
      result.ressources.reserve (data.at ("Ressource").size ());
      for (const auto &d : data["Ressource"])
        {
          result.ressources.emplace_back (
              static_cast<RessourceType> (d["id"].get<int> ()),
              d["Quantity"].get<double> ());
        }
    }

  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing saved achievements :\n"
                << e.what () << '\n';
      abort ();
    }

  try
    {
      result.jellies.numJellies
          = data.at ("Jellies").at ("num").get<unsigned> ();
      result.jellies.maxNumJellies
          = data.at ("Jellies").at ("numMax").get<unsigned> ();

      for (const auto &job : data.at ("Jellies").at ("Jobs"))
        {
          result.jellies.jobNumbers.push_back (
              { JellyJob (job.at ("id").get<int> ()),
                job.at ("num").get<unsigned> () });
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing saved jellies & jobs :\n"
                << e.what () << '\n';
      abort ();
    }

  try
    {

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

      result.cultures.reserve (data.at ("Culture").size ());
      for (const auto &c : data["Culture"])
        {
          result.cultures.emplace_back (
              static_cast<AquaCultureID> (c["id"].get<int> ()),
              CultureData{
                  c["Ongoing"].get<bool> (),
                  c["Fields"].get<unsigned> (),
              });
        }

      return result;
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing the rest :\n" << e.what () << '\n';
      abort ();
    }
}