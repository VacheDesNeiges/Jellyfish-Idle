#include "GameDataAccess.hpp"
#include "AbilityDataView.hpp"
#include "AchievementDataView.hpp"
#include "BuildingDataView.hpp"
#include "CraftingDataView.hpp"
#include "DepthDataView.hpp"
#include "GameDataView.hpp"
#include "GardenDataView.hpp"
#include "JellyfishDataView.hpp"
#include "MultiplierDataView.hpp"
#include "RessourceDataView.hpp"
#include "UpgradeDataView.hpp"
#include <cassert>
#include <memory>

void
GameDataAccess::bindDataView (std::shared_ptr<GameDataView> v)
{
  assert (view == nullptr);
  view = v;
}

std::shared_ptr<const GameDataView>
GameDataAccess::getDataView () const
{
  assert (view != nullptr);
  return view;
}

std::shared_ptr<const MultiplierDataView>
GameDataAccess::multipliersView () const
{
  assert (view != nullptr);
  return view->getMultiplierView ();
}

std::shared_ptr<const RessourceDataView>
GameDataAccess::ressourcesView () const
{
  assert (view != nullptr);
  return view->getRessourcesView ();
}

std::shared_ptr<const JellyFishDataView>
GameDataAccess::jelliesView () const
{
  assert (view != nullptr);
  return view->getJelliesView ();
}

std::shared_ptr<const BuildingDataView>
GameDataAccess::buildingsView () const
{
  assert (view != nullptr);
  return view->getBuildingsView ();
}

std::shared_ptr<const AchievementDataView>
GameDataAccess::achievementsView () const
{
  assert (view != nullptr);
  return view->getAchievementsView ();
}

std::shared_ptr<const DepthDataView>
GameDataAccess::depthView () const
{
  assert (view != nullptr);
  return view->getDepthView ();
}

std::shared_ptr<const UpgradeDataView>
GameDataAccess::upgradeView () const
{
  assert (view != nullptr);
  return view->getUpgradeView ();
}

std::shared_ptr<const CraftDataView>
GameDataAccess::craftView () const
{
  return view->getCraftView ();
}

std::shared_ptr<const GardenDataView>
GameDataAccess::gardenView () const
{
  return view->getGardenView ();
}

std::shared_ptr<const AbilityDataView>
GameDataAccess::abilitiesView () const
{
  return view->getAbilitiesView ();
}