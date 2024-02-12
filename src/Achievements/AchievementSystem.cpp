#include "AchievementSystem.hpp"

#include "Achievement.hpp"
#include "AchievementDataView.hpp"
#include "AchievementIDs.hpp"
#include "Building.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
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
               >= 0.3;
      } },

    { Mines, [this] () { return depthView ()->getCurrentDepth () >= 20; } },

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
      [this] () { return depthView ()->getCurrentDepth () >= 10; } },

    { RessourceGlass,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Glass)
               > 0;
      } },

    { RessourceStoneSlab,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (
                   RessourceType::StoneSlab)
               > 0;
      } },

    { RessourceGlassPane,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (
                   RessourceType::GlassPane)
               > 0;
      } }
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

bool
AchievementSystem::isUnlocked (BuildingType t) const
{
  using enum BuildingType;
  switch (t)
    {
    case PlanktonField:
      return isUnlocked (AchievementIDs::PlanktonField);

    case SandCurrentDucts:
      return isUnlocked (AchievementIDs::FirstSandNest);

    case DuneShelter:
      return isUnlocked (AchievementIDs::FirstSandNest);

    case Mines:
      return isUnlocked (AchievementIDs::Mines);

    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (JellyJobs j) const
{
  using enum JellyJobs;
  using enum AchievementIDs;
  switch (j)
    {
    case GatherSand:
      return isUnlocked (FirstJelly);

    case ExploreTheDepths:
      return isUnlocked (JobExploreTheDepths);

    case FocusForInsight:
      return isUnlocked (FocusingUpgradeBought);

    case Mining:
      return isUnlocked (JobMining);

    case Artisan:
      return isUnlocked (JobArtisan);

    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (RessourceType r) const
{

  switch (r)
    {
      using enum AchievementIDs;
      using enum RessourceType;

    case Food:
      return true;

    case Sand:
      return isUnlocked (FirstJelly);

    case Stone:
      return isUnlocked (JobMining);

    case Insight:
      return isUnlocked (FocusingUpgradeBought);

    case Glass:
      return isUnlocked (LightningAbilityBuyable);

    case StoneSlab:
      return isUnlocked (RessourceStoneSlab);

    case GlassPane:
      return isUnlocked (RessourceGlassPane);

    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (AbilityType t) const
{
  using enum AbilityType;
  switch (t)
    {
    case CallThunder:
      return isUnlocked (AchievementIDs::LightningAbilityBuyable);
    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (UpgradeID id) const
{
  switch (id)
    {
      using enum AchievementIDs;
      using enum UpgradeID;

    case Focusing:
      return isUnlocked (AncientOctopus);

    case Telekinesis:
      return isUnlocked (FocusingUpgradeBought);

    case AdvancedTelekinesis:
      return isUnlocked (TelekinesisUpgradeBought);

    case Writing:
      return isUnlocked (AdvancedTelekinesisUpgradeBought);

    default:
      return false;
    }
}