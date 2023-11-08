#pragma once

#include "Achievement.hpp"
#include "Building.hpp"
#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include <string>
#include <utility>
#include <vector>

struct SaveData
{
  std::vector<std::pair<BuildingType, unsigned> > buildings;
  std::vector<std::pair<AchievementIDs, bool> > achievements;
  std::vector<std::pair<RessourceType, double> > ressources;
  JellyFishData jellies;
};

class SaveSystem
{
public:
  static void save (const std::vector<std::pair<BuildingType, unsigned> > &,
                    const std::vector<std::pair<AchievementIDs, bool> > &,
                    const std::vector<std::pair<RessourceType, double> > &,
                    const JellyFishData &);
  static SaveData loadFromFile ();

  static constexpr std::string saveFileName = "save.json";
};
