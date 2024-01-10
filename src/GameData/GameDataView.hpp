#pragma once
#include "AbilityDataView.hpp"
#include "AchievementDataView.hpp"
#include "BuildingDataView.hpp"
#include "DepthDataView.hpp"
#include "JellyfishDataView.hpp"
#include "RessourceDataView.hpp"
#include "UpgradeDataView.hpp"

#include <memory>

// --- Forward Declarations to avoid circular dependencies ---

class RessourceManager;
class BuildingManager;
class JellyfishManager;
class AchievementSystem;
class AbilityManager;
class DepthSystem;
class UpgradeManager;

// Gives a read only access to the variables of the game
class GameDataView
{
public:
  GameDataView (std::shared_ptr<RessourceManager>,
                std::shared_ptr<BuildingManager>,
                std::shared_ptr<JellyfishManager>,
                std::shared_ptr<AchievementSystem>,
                std::shared_ptr<AbilityManager>, std::shared_ptr<DepthSystem>,
                std::shared_ptr<UpgradeManager>);

  std::shared_ptr<RessourceDataView> getRessourcesView () const;
  std::shared_ptr<BuildingDataView> getBuildingsView () const;
  std::shared_ptr<JellyFishDataView> getJelliesView () const;
  std::shared_ptr<AchievementDataView> getAchievementsView () const;
  std::shared_ptr<AbilityDataView> getAbilitiesView () const;
  std::shared_ptr<DepthDataView> getDepthView () const;
  std::shared_ptr<UpgradeDataView> getUpgradeView () const;

private:
  std::shared_ptr<RessourceDataView> ressources;
  std::shared_ptr<BuildingDataView> buildings;
  std::shared_ptr<JellyFishDataView> jellies;
  std::shared_ptr<AchievementDataView> achievements;
  std::shared_ptr<AbilityDataView> abilities;
  std::shared_ptr<DepthDataView> depth;
  std::shared_ptr<UpgradeDataView> upgrades;
};