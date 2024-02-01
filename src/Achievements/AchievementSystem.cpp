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

  for (const auto a : allAchievementsIDs)
    {
      achievements.emplace (a, Achievement ());
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
        return getDataView ()->getDepthView ()->getCurrentDepth () >= 30;
      } },

    { FirstJelly,
      [this] () {
        return getDataView ()->getJelliesView ()->getNumJellies () >= 1;
      } },

    { JobExploreTheDepths,
      [this] () {
        return getDataView ()->getJelliesView ()->getNumJellies () >= 2;
      } },

    { JobMining,
      [this] () {
        return getDataView ()->getUpgradeView ()->isBought (
            UpgradeID::Telekinesis);
      } },

    { JobArtisan,
      [this] () {
        return getDataView ()->getUpgradeView ()->isBought (
            UpgradeID::AdvancedTelekinesis);
      } },

    { FocusingUpgradeBought,
      [this] () {
        return getDataView ()->getUpgradeView ()->isBought (
            UpgradeID::Focusing);
      } },

    { LightningAbilityBuyable,
      [this] () {
        return getDataView ()->getRessourcesView ()->getRessourceQuantity (
                   RessourceType::Insight)
               >= 1;
      } },

    { ResearchTabUnlocked, [] () { return false; } },

    { AncientOctopus,
      [this] () {
        return getDataView ()->getDepthView ()->getCurrentDepth () >= 20;
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
  for (const auto &id : allAchievementsIDs)
    {
      using enum AchievementIDs;
      if (isUnlocked (id))
        continue;

      if (achievementConditions[id]())
        unlock (id);
    }
}