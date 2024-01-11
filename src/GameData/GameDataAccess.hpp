#pragma once
#include "AchievementDataView.hpp"
#include "DepthDataView.hpp"
#include "GameDataView.hpp"
#include "UpgradeDataView.hpp"
#include <memory>

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
  std::shared_ptr<UpgradeDataView> upgradeView () const;

private:
  static inline std::shared_ptr<GameDataView> view = nullptr;
};