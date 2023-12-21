#include "AchievementSystem.hpp"
#include "Achievement.hpp"
#include "BuildingDataView.hpp"
#include "DepthDataView.hpp"
#include "JellyfishDataView.hpp"
#include "Ressource.hpp"
#include "RessourceDataView.hpp"
#include <utility>
#include <vector>

AchievementSystem::AchievementSystem ()
{
  using enum AchievementIDs;

  for (auto a = static_cast<int> (PlanktonField); a != static_cast<int> (Last);
       a++)
    {
      achievements.emplace (static_cast<AchievementIDs> (a), Achievement ());
    }

  achievementConditions = {
    { PlanktonField,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Food)
               >= 5;
      } },

    { FirstSandNest,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Sand)
               >= 1;
      } },

    { FirstJelly,
      [this] () {
        return getDataView ()->getJelliesView ()->getNumJellies () >= 1;
      } },

    { JobFocusing,
      [this] () {
        return getDataView ()->getBuildingsView ()->getBuildingQuantity (
                   BuildingType::SandNest)
               >= 1;
      } },

    { JobExploreTheDepths,
      [this] () {
        return getDataView ()->getJelliesView ()->getNumJellies () >= 1;
      } },

    { FirstInsightAbility,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Insight)
               >= 1;
      } },

    { ResearchTabUnlocked, [] () { return false; } },
    { ReachedDepth100,
      [this] () {
        return getDataView ()->getDepthView ()->getCurrentDepth () >= 100;
      } }
  };
}

bool
AchievementSystem::isUnlocked (AchievementIDs id)
{
  return achievements[id].isUnlocked ();
}

void
AchievementSystem::unlock (AchievementIDs id)
{
  achievements[id].unlock ();
}

std::vector<std::pair<AchievementIDs, bool> >
AchievementSystem::getData () const
{
  std::vector<std::pair<AchievementIDs, bool> > result;

  for (const auto &[id, val] : achievements)
    {
      result.emplace_back (id, val.isUnlocked ());
    }
  return result;
}

void
AchievementSystem::loadData (
    const std::vector<std::pair<AchievementIDs, bool> > &data)
{
  for (const auto &[id, unlockedState] : data)
    {
      achievements[id].setState (unlockedState);
    }
}

void
AchievementSystem::checkAchievements ()
{
  using enum AchievementIDs;
  for (auto a = static_cast<int> (PlanktonField); a != static_cast<int> (Last);
       a++)
    {
      auto id = static_cast<AchievementIDs> (a);
      using enum AchievementIDs;
      if (isUnlocked (id))
        continue;

      if (achievementConditions[id]())
        unlock (id);
    }
}