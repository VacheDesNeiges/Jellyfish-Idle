#pragma once
#include "AbilityManager.hpp"
#include "Achievement.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include "RessourceManager.hpp"
#include <functional>
#include <map>

#include "DepthSystem.hpp"

class GameDataSynchronizer
{

public:
  GameDataSynchronizer ();

  void save () const;
  void loadSave ();
  void gameTick ();

  void gatherFood ();
  void buy (BuildingType);
  bool isBuyable (BuildingType);

  double getRessourceQuantity (RessourceType);
  double getRessourceMaxQuantity (RessourceType);
  std::string_view getRessourceName (RessourceType);
  double getRessourceProduction (RessourceType);
  double getRessourceConsumption (RessourceType);

  unsigned getBuildingQuantity (BuildingType);
  std::list<std::pair<RessourceType, double> >
      getBuildingProduction (BuildingType);

  std::string getBuildingName (BuildingType);
  std::string getBuildingDescription (BuildingType);
  std::string getAdvancedBuildingDescription (BuildingType);

  std::string getJobDescription (JellyJobs) const;
  std::string getAbilityName (AbilityType);
  std::string getAbilityDescription (AbilityType);

  unsigned long getNumJellies () const;
  long getNumJellies (JellyJobs);
  unsigned long getMaxNumJellies () const;
  bool unassignJelly (JellyJobs);
  bool assignJelly (JellyJobs);

  bool isUnlocked (BuildingType);
  bool isUnlocked (JellyJobs);
  bool isUnlocked (AchievementIDs);
  bool isUnlocked (RessourceType);
  bool isUnlocked (AbilityType);
  void unlock (AchievementIDs);

  void useAbility (AbilityType);
  bool isUsable (AbilityType);

  unsigned getCurrentDepth () const;
  float getDepthProgress () const;

private:
  RessourceManager ressources;
  BuildingManager buildings;
  JellyfishManager jellies;
  AchievementSystem achievements;
  AbilityManager abilities;
  std::map<AchievementIDs, std::function<bool ()> > achievementConditions;
  DepthSystem depth;

  void checkAchievements ();
  void checkJellyfishArrival ();

  std::map<RessourceType, double>
  addMaps (const std::map<RessourceType, double> &,
           const std::map<RessourceType, double> &) const;
  void updateMaxNumJellies ();
};