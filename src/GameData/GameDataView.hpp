#pragma once
#include "AbilityDataView.hpp"
#include "AchievementDataView.hpp"
#include "BuildingDataView.hpp"
#include "CraftingDataView.hpp"
#include "DepthDataView.hpp"
#include "GardenDataView.hpp"
#include "JellyfishDataView.hpp"
#include "MultiplierDataView.hpp"
#include "RessourceDataView.hpp"
#include "UpgradeDataView.hpp"

#include <memory>

// --- Forward Declarations to avoid circular dependencies ---

struct SystemPtrs;

// Gives a read only access to the variables of the game
class GameDataView
{
public:
  explicit GameDataView (std::shared_ptr<SystemPtrs>);

  std::shared_ptr<RessourceDataView> getRessourcesView () const;
  std::shared_ptr<BuildingDataView> getBuildingsView () const;
  std::shared_ptr<JellyFishDataView> getJelliesView () const;
  std::shared_ptr<AchievementDataView> getAchievementsView () const;
  std::shared_ptr<AbilityDataView> getAbilitiesView () const;
  std::shared_ptr<DepthDataView> getDepthView () const;
  std::shared_ptr<UpgradeDataView> getUpgradeView () const;
  std::shared_ptr<MultiplierDataView> getMultiplierView () const;
  std::shared_ptr<CraftDataView> getCraftView () const;
  std::shared_ptr<GardenDataView> getGardenView () const;

private:
  std::shared_ptr<SystemPtrs> systems;

  std::shared_ptr<RessourceDataView> ressourcesView;
  std::shared_ptr<BuildingDataView> buildingsView;
  std::shared_ptr<JellyFishDataView> jelliesView;
  std::shared_ptr<AchievementDataView> achievementsView;
  std::shared_ptr<AbilityDataView> abilitiesView;
  std::shared_ptr<DepthDataView> depthView;
  std::shared_ptr<UpgradeDataView> upgradesView;
  std::shared_ptr<MultiplierDataView> multipliersView;
  std::shared_ptr<CraftDataView> craftView;
  std::shared_ptr<GardenDataView> gardenView;
};