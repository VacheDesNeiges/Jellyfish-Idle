#include "GameDataView.hpp"
#include "AbilityDataView.hpp"
#include "AbilityManager.hpp"
#include "AchievementDataView.hpp"
#include "AchievementSystem.hpp"
#include "BuildingDataView.hpp"
#include "BuildingManager.hpp"
#include "DepthDataView.hpp"
#include "DepthSystem.hpp"
#include "JellyfishDataView.hpp"
#include "JellyfishManager.hpp"
#include "RessourceDataView.hpp"
#include "RessourceManager.hpp"
#include <memory>

GameDataView::GameDataView (std::shared_ptr<RessourceManager> r,
                            std::shared_ptr<BuildingManager> b,
                            std::shared_ptr<JellyfishManager> j,
                            std::shared_ptr<AchievementSystem> ach,
                            std::shared_ptr<AbilityManager> abi,
                            std::shared_ptr<DepthSystem> d)

    : ressources (std::make_shared<RessourceDataView> (r)),
      buildings (std::make_shared<BuildingDataView> (b, r)),
      jellies (std::make_shared<JellyFishDataView> (j)),
      achievements (std::make_shared<AchievementDataView> (ach)),
      abilities (std::make_shared<AbilityDataView> (abi, r)),
      depth (std::make_shared<DepthDataView> (d))
{
}

std::shared_ptr<RessourceDataView>
GameDataView::getRessourcesView () const
{
  return ressources;
}

std::shared_ptr<BuildingDataView>
GameDataView::getBuildingsView () const
{
  return buildings;
}

std::shared_ptr<JellyFishDataView>
GameDataView::getJelliesView () const
{
  return jellies;
}

std::shared_ptr<AchievementDataView>
GameDataView::getAchievementsView () const
{
  return achievements;
}

std::shared_ptr<AbilityDataView>
GameDataView::getAbilitiesView () const
{
  return abilities;
}

std::shared_ptr<DepthDataView>
GameDataView::getDepthView () const
{
  return depth;
}