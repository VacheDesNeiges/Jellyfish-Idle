#pragma once

#include "AquaCulture.hpp"
#include "Building.hpp"
#include "CraftingRecipe.hpp"
#include "DepthSystem.hpp"
#include "GameIDsTypes.hpp"
#include "JellyfishManager.hpp"
#include "UpgradeId.hpp"
#include <string>
#include <utility>
#include <vector>

struct SaveData
{
  std::vector<std::pair<BuildingType, unsigned> > buildings;
  std::vector<std::pair<AchievementIDs, bool> > achievements;
  std::vector<std::pair<RessourceType, double> > ressources;
  JellyfishData jellies;
  DepthData depth;
  std::vector<std::pair<UpgradeID, bool> > upgrades;
  std::vector<std::pair<RecipeID, RecipeSaveData> > crafts;
  std::vector<std::pair<AquaCultureID, CultureData> > cultures;
};

class SaveSystem
{
public:
  static void save (const SaveData &);
  static SaveData loadFromFile (std::string);

  static constexpr std::string saveFileName = "save.json";
};
