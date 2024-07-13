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

  std::shared_ptr<const RessourceDataView> getRessourcesView () const;
  std::shared_ptr<const BuildingDataView> getBuildingsView () const;
  std::shared_ptr<const JellyFishDataView> getJelliesView () const;
  std::shared_ptr<const AchievementDataView> getAchievementsView () const;
  std::shared_ptr<const AbilityDataView> getAbilitiesView () const;
  std::shared_ptr<const DepthDataView> getDepthView () const;
  std::shared_ptr<const UpgradeDataView> getUpgradeView () const;
  std::shared_ptr<const MultiplierDataView> getMultiplierView () const;
  std::shared_ptr<const CraftDataView> getCraftView () const;
  std::shared_ptr<const GardenDataView> getGardenView () const;

private:
  std::shared_ptr<SystemPtrs> systems;

  std::shared_ptr<const RessourceDataView> ressourcesView;
  std::shared_ptr<const BuildingDataView> buildingsView;
  std::shared_ptr<const JellyFishDataView> jelliesView;
  std::shared_ptr<const AchievementDataView> achievementsView;
  std::shared_ptr<const AbilityDataView> abilitiesView;
  std::shared_ptr<const DepthDataView> depthView;
  std::shared_ptr<const UpgradeDataView> upgradesView;
  std::shared_ptr<const MultiplierDataView> multipliersView;
  std::shared_ptr<const CraftDataView> craftView;
  std::shared_ptr<const GardenDataView> gardenView;
};