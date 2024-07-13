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
  std::shared_ptr<const GameDataView> getDataView () const;
  std::shared_ptr<const MultiplierDataView> multipliersView () const;
  std::shared_ptr<const RessourceDataView> ressourcesView () const;
  std::shared_ptr<const JellyFishDataView> jelliesView () const;
  std::shared_ptr<const BuildingDataView> buildingsView () const;
  std::shared_ptr<const AchievementDataView> achievementsView () const;
  std::shared_ptr<const DepthDataView> depthView () const;
  std::shared_ptr<const CraftDataView> craftView () const;
  std::shared_ptr<const UpgradeDataView> upgradeView () const;
  std::shared_ptr<const GardenDataView> gardenView () const;

private:
  static inline std::shared_ptr<GameDataView> view = nullptr;
};