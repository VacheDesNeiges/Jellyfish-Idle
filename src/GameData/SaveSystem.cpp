#include "SaveSystem.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
#include "DepthSystem.hpp"
#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

void
SaveSystem::save (
    const std::vector<std::pair<BuildingType, unsigned> > &buildingsData,
    const std::vector<std::pair<AchievementIDs, bool> > &achievementsData,
    const std::vector<std::pair<RessourceType, double> > &ressourcesData,
    const JellyFishData &jfishData, const DepthData &depthData)
{
  nlohmann::json j;
  for (const auto &[type, quant] : buildingsData)
    {
      j["Building"]
          += { { "id", static_cast<unsigned> (type) }, { "Quantity", quant } };
    }

  for (const auto &[idAch, isUnlocked] : achievementsData)
    {
      j["Achievement"] += { { "id", static_cast<unsigned> (idAch) },
                            { "Unlocked", isUnlocked } };
    }

  for (const auto &[idRes, quant] : ressourcesData)
    {
      j["Ressource"] += { { "id", static_cast<unsigned> (idRes) },
                          { "Quantity", quant } };
    }

  j["Jellies"] += { { "num", jfishData.numJellies },
                    { "numMax", jfishData.maxNumJellies },
                    { "numJobNone", jfishData.numJobNone },
                    { "numJobExplore", jfishData.numJobExploreTheDepths },
                    { "numJobGatherSand", jfishData.numJobGatheringSand },
                    { "numJobFocusing", jfishData.numJobFocusing } };

  j["Depth"] += { { "currentDepth", depthData.currentDepth },
                  { "currentProg", depthData.currentProg } };

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

  for (const auto &d : data["Building"])
    {
      result.buildings.emplace_back (
          static_cast<BuildingType> (d["id"].get<unsigned> ()),
          d["Quantity"].get<unsigned> ());
    }

  for (const auto &d : data["Achievement"])
    {
      result.achievements.emplace_back (
          static_cast<AchievementIDs> (d["id"].get<unsigned> ()),
          d["Unlocked"].get<bool> ());
    }

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
  result.jellies.numJobGatheringSand
      = data["Jellies"][0]["numJobGatherSand"].get<unsigned> ();
  result.jellies.numJobFocusing
      = data["Jellies"][0]["numJobFocusing"].get<unsigned> ();

  result.depth.currentDepth
      = data["Depth"][0]["currentDepth"].get<unsigned> ();
  result.depth.currentProg = data["Depth"][0]["currentProg"].get<float> ();

  return result;
}