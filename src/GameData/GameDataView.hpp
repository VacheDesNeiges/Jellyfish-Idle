#pragma once
#include <memory>

// --- Forward Declarations to avoid circular dependecies ---

class RessourceManager;
class RessourceDataView;

class BuildingManager;
class BuildingDataView;

class JellyfishManager;
class JellyFishDataView;

class AchievementSystem;
class AchievementDataView;

class AbilityManager;
class AbilityDataView;

class DepthSystem;
class DepthDataView;

//-----------------------------------------------------------

class GameDataView
{
public:
  GameDataView (std::shared_ptr<RessourceManager>,
                std::shared_ptr<BuildingManager>,
                std::shared_ptr<JellyfishManager>,
                std::shared_ptr<AchievementSystem>,
                std::shared_ptr<AbilityManager>, std::shared_ptr<DepthSystem>);

  std::shared_ptr<RessourceDataView> getRessourcesView () const;
  std::shared_ptr<BuildingDataView> getBuildingsView () const;
  std::shared_ptr<JellyFishDataView> getJelliesView () const;
  std::shared_ptr<AchievementDataView> getAchievementsView () const;
  std::shared_ptr<AbilityDataView> getAbilitiesView () const;
  std::shared_ptr<DepthDataView> getDepthView () const;

private:
  std::shared_ptr<RessourceDataView> ressources;
  std::shared_ptr<BuildingDataView> buildings;
  std::shared_ptr<JellyFishDataView> jellies;
  std::shared_ptr<AchievementDataView> achievements;
  std::shared_ptr<AbilityDataView> abilities;
  std::shared_ptr<DepthDataView> depth;
};