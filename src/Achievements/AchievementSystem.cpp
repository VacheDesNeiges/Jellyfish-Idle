#include "AchievementSystem.hpp"

#include "Achievement.hpp"
#include "AchievementIDs.hpp"
#include "Ressource.hpp"
#include "UpgradeId.hpp"
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
               >= 3;
      } },

    { Mines,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Stone)
               >= 5;
      } },

    { FirstJelly,
      [this] () {
        return getDataView ()->getJelliesView ()->getNumJellies () >= 1;
      } },

    { JobExploreTheDepths,
      [this] () {
        return getDataView ()->getJelliesView ()->getNumJellies () >= 2;
      } },

    { LightningAbilityBuyable,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Insight)
               >= 1;
      } },

    { ResearchTabUnlocked, [] () { return false; } },

    { JobMining,
      [this] () {
        return getDataView ()->getDepthView ()->getCurrentDepth () >= 30;
      } },

    { JobFocusing,
      [this] () {
        return getDataView ()->getUpgradeView ()->isBought (
            UpgradeID::FocusingForInsight);
      } },

    { AncientOctopus,
      [this] () {
        return getDataView ()->getDepthView ()->getCurrentDepth () >= 20;
      } },

    { FocusForInsightUpgrade,
      [this] () {
        return getDataView ()->getUpgradeView ()->isBought (
            UpgradeID::FocusingForInsight);
      } },
    { RessourceGlass,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Glass)
               > 0;
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
  for (auto a = static_cast<int> (PlanktonField);
       a != static_cast<int> (Last); // TODO change for a constexpr array
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