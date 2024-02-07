#include "AchievementSystem.hpp"

#include "Achievement.hpp"
#include "AchievementIDs.hpp"
#include "Ressource.hpp"
#include "UpgradeId.hpp"

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

AchievementSystem::AchievementSystem ()
{
  using enum AchievementIDs;
  achievements.reserve (allAchievementsIDs.size ());
  achievementConditions.reserve (allAchievementsIDs.size ());
  for (const auto a : allAchievementsIDs)
    {
      achievements.emplace (a, Achievement ());
    }

  achievementConditions = {
    { PlanktonField,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Food)
               >= 5;
      } },

    { FirstSandNest,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Sand)
               >= 3;
      } },

    { Mines, [this] () { return depthView ()->getCurrentDepth () >= 30; } },

    { FirstJelly,
      [this] () { return jelliesView ()->getNumJellies () >= 1; } },

    { JobExploreTheDepths,
      [this] () { return jelliesView ()->getNumJellies () >= 2; } },

    { JobMining,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::Telekinesis);
      } },

    { JobArtisan,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::AdvancedTelekinesis);
      } },

    { FocusingUpgradeBought,
      [this] () { return upgradeView ()->isBought (UpgradeID::Focusing); } },

    { TelekinesisUpgradeBought,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::Telekinesis);
      } },

    { AdvancedTelekinesisUpgradeBought,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::AdvancedTelekinesis);
      } },

    { LightningAbilityBuyable,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Insight)
               >= 1;
      } },

    { ResearchTabUnlocked, [] () { return false; } },

    { AncientOctopus,
      [this] () { return depthView ()->getCurrentDepth () >= 20; } },

    { RessourceGlass,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Glass)
               > 0;
      } },

  };

  for (const auto &id : allAchievementsIDs)
    {
      assert (achievementConditions.contains (id)
              || std::cerr << "Missing achievement enum val : "
                           << static_cast<int> (id) << "\n");
    }
}

bool
AchievementSystem::isUnlocked (AchievementIDs id) const
{
  return achievements.at (id).isUnlocked ();
}

void
AchievementSystem::unlock (AchievementIDs id)
{
  achievements.at (id).unlock ();
}

std::vector<std::pair<AchievementIDs, bool> >
AchievementSystem::getData () const
{
  std::vector<std::pair<AchievementIDs, bool> > result;
  result.reserve (allAchievementsIDs.size ());
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