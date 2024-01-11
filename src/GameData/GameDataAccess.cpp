#include "GameDataAccess.hpp"
#include "AchievementDataView.hpp"
#include "BuildingDataView.hpp"
#include "DepthDataView.hpp"
#include "GameDataView.hpp"
#include "JellyfishDataView.hpp"
#include "MultiplierDataView.hpp"
#include "RessourceDataView.hpp"
#include "UpgradeDataView.hpp"
#include <cassert>
#include <iostream>
#include <memory>

void
GameDataAccess::bindDataView (std::shared_ptr<GameDataView> v)
{
  assert (view == nullptr);
  view = v;
}

std::shared_ptr<GameDataView>
GameDataAccess::getDataView () const
{
  assert (view != nullptr);
  return view;
}

std::shared_ptr<MultiplierDataView>
GameDataAccess::multipliersView () const
{
  assert (view != nullptr);
  return view->getMultiplierView ();
}

std::shared_ptr<RessourceDataView>
GameDataAccess::ressourcesView () const
{
  assert (view != nullptr);
  return view->getRessourcesView ();
}

std::shared_ptr<JellyFishDataView>
GameDataAccess::jelliesView () const
{
  assert (view != nullptr);
  return view->getJelliesView ();
}

std::shared_ptr<BuildingDataView>
GameDataAccess::buildingsView () const
{
  assert (view != nullptr);
  return view->getBuildingsView ();
}

std::shared_ptr<AchievementDataView>
GameDataAccess::achievementsView () const
{
  assert (view != nullptr);
  return view->getAchievementsView ();
}

std::shared_ptr<DepthDataView>
GameDataAccess::depthView () const
{
  assert (view != nullptr);
  return view->getDepthView ();
}

std::shared_ptr<UpgradeDataView>
GameDataAccess::upgradeView () const
{
  assert (view != nullptr);
  return view->getUpgradeView ();
}