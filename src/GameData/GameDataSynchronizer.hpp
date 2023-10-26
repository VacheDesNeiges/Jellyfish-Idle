#pragma once
#include "Achievement.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include "RessourceManager.hpp"
#include <map>

class GameDataSynchronizer
{

public:
  void loadSave ();
  void gameTick ();

  void gatherFood ();
  void buy (BuildingType);
  bool isBuyable (BuildingType);

  double getRessourceQuantity (RessourceType);
  double getRessourceMaxQuantity (RessourceType);
  std::string_view getRessourceName (RessourceType);

  unsigned getBuildingQuantity (BuildingType);
  std::list<std::pair<RessourceType, double> >
      getBuildingProduction (BuildingType);

  std::string getBuildingName (BuildingType);
  std::string getBuildingDescription (BuildingType);
  std::string getAdvancedBuildingDescription (BuildingType);

  unsigned long getNumJellies () const;
  long getNumJellies (JellyJobs);
  unsigned long getMaxNumJellies () const;
  bool unassignJelly (JellyJobs);
  bool assignJelly (JellyJobs);

  bool isUnlocked (BuildingType);
  bool isUnlocked (AchievementIDs);
  void unlock (AchievementIDs);

private:
  RessourceManager ressources;
  BuildingManager buildings;
  JellyfishManager jellies;
  AchievementSystem achievements;

  void checkAchievements ();
  void checkJellyfishArrival ();

  std::map<RessourceType, double>
  addMaps (const std::map<RessourceType, double> &,
           const std::map<RessourceType, double> &) const;
  void updateMaxNumJellies ();
};