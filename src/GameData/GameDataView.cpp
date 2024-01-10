#include "GameDataView.hpp"

#include "AbilityDataView.hpp"
#include "AchievementDataView.hpp"
#include "BuildingDataView.hpp"
#include "DepthDataView.hpp"
#include "JellyfishDataView.hpp"
#include "MultiplierDataView.hpp"
#include "RessourceDataView.hpp"
#include "UpgradeDataView.hpp"

#include "GameSystems.hpp"

#include <memory>

GameDataView::GameDataView (std::shared_ptr<SystemPtrs> s) : systems (s)

{
  ressourcesView = std::make_shared<RessourceDataView> (systems->ressources);
  buildingsView = std::make_shared<BuildingDataView> (systems->buildings,
                                                      systems->ressources);
  jelliesView = std::make_shared<JellyFishDataView> (systems->jellies);
  achievementsView
      = std::make_shared<AchievementDataView> (systems->achievements);
  abilitiesView = std::make_shared<AbilityDataView> (systems->abilities,
                                                     systems->ressources);
  depthView = std::make_shared<DepthDataView> (systems->depth);
  upgradesView = std::make_shared<UpgradeDataView> (systems->upgrades,
                                                    systems->ressources);
  multipliersView
      = std::make_shared<MultiplierDataView> (systems->multipliers);
}

std::shared_ptr<RessourceDataView>
GameDataView::getRessourcesView () const
{
  return ressourcesView;
}

std::shared_ptr<BuildingDataView>
GameDataView::getBuildingsView () const
{
  return buildingsView;
}

std::shared_ptr<JellyFishDataView>
GameDataView::getJelliesView () const
{
  return jelliesView;
}

std::shared_ptr<AchievementDataView>
GameDataView::getAchievementsView () const
{
  return achievementsView;
}

std::shared_ptr<AbilityDataView>
GameDataView::getAbilitiesView () const
{
  return abilitiesView;
}

std::shared_ptr<DepthDataView>
GameDataView::getDepthView () const
{
  return depthView;
}

std::shared_ptr<UpgradeDataView>
GameDataView::getUpgradeView () const
{
  return upgradesView;
}

std::shared_ptr<MultiplierDataView>
GameDataView::getMultiplierView () const
{
  return multipliersView;
}