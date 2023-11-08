#include "SaveSystem.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
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
    const JellyFishData &jfishData)
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

  j["Jellies"] += { { "num" },
                    { jfishData.numJellies },
                    { "numMax", jfishData.maxNumJellies },
                    { "numJobNone", jfishData.numJobNone },
                    { "numJobExplore", jfishData.numJobExploreTheSea },
                    { "numJobGatherSand", jfishData.numJobGatheringSand },
                    { "numJobFocusing", jfishData.numJobFocusing } };

  std::ofstream file (saveFileName);
  file << j;
}

SaveData
SaveSystem::loadFromFile ()
{
  SaveData result;

  std::ifstream f (saveFileName);
  nlohmann::json data = nlohmann::json::parse (f);

  for (const auto &d : data["Building"])
    {
      result.buildings.push_back (
          std::make_pair (static_cast<BuildingType> (d["id"].get<unsigned> ()),
                          d["Quantity"].get<unsigned> ()));
    }

  for (const auto &d : data["Achievement"])
    {
      result.achievements.push_back (std::make_pair (
          static_cast<AchievementIDs> (d["id"].get<unsigned> ()),
          d["Unlocked"].get<bool> ()));
    }

  for (const auto &d : data["Ressource"])
    {
      result.ressources.push_back (std::make_pair (
          static_cast<RessourceType> (d["id"].get<unsigned> ()),
          d["Quantity"].get<double> ()));
    }

  return result;
}