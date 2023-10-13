#pragma once
#include "Achievement.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "Ressource.hpp"
#include "RessourceManager.hpp"
#include <map>
#include <src/Jellyfishs/Jellyfish.hpp>
#include <src/Jellyfishs/JellyfishManager.hpp>

class GameDataSynchronizer
{

public:
  void loadSave (); // TODO implement save and load system
  void gameTick ();

  void gatherFood ();
  void buy (BuildingType);

  double getRessourceQuantity (RessourceType);
  double getRessourceMaxQuantity (RessourceType);
  std::string_view getRessourceName (RessourceType);

  unsigned getBuildingQuantity (BuildingType);
  std::list<std::pair<RessourceType, double> >
      getBuildingProduction (BuildingType);

  unsigned long getNumJellies ();
  long getNumJellies (JellyJobs);
  unsigned long getMaxNumJellies ();

  bool unassignJelly (JellyJobs);
  bool assignJelly (JellyJobs);

  bool isUnlocked (AchievementIDs);
  void unlock (AchievementIDs);

private:
  RessourceManager ressources;
  BuildingManager buildings;
  JellyfishManager jellies;
  AchievementSystem achievements;
};