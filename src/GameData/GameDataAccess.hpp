#pragma once
#include "AchievementDataView.hpp"
#include "CraftingDataView.hpp"
#include "DepthDataView.hpp"
#include "GameDataView.hpp"
#include "UpgradeDataView.hpp"
#include <memory>

/**
 * @brief Interface giving access to a read only view of the game state
 *
 */
class GameDataAccess
{
public:
  static void bindDataView (std::shared_ptr<GameDataView>);

protected:
  std::shared_ptr<GameDataView> getDataView () const;
  std::shared_ptr<MultiplierDataView> multipliersView () const;
  std::shared_ptr<RessourceDataView> ressourcesView () const;
  std::shared_ptr<JellyFishDataView> jelliesView () const;
  std::shared_ptr<BuildingDataView> buildingsView () const;
  std::shared_ptr<AchievementDataView> achievementsView () const;
  std::shared_ptr<DepthDataView> depthView () const;
  std::shared_ptr<CraftDataView> craftView () const;
  std::shared_ptr<UpgradeDataView> upgradeView () const;
  std::shared_ptr<GardenDataView> gardenView () const;

private:
  static inline std::shared_ptr<GameDataView> view = nullptr;
};