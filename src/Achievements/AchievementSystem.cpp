#include "AchievementSystem.hpp"

#include "Achievement.hpp"
#include "AchievementDataView.hpp"
#include "AchievementIDs.hpp"
#include "Building.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "UpgradeId.hpp"

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
  initLambdas ();
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
      using enum AchievementIDs;
    case AquaticField:
      return isUnlocked (BuildingAquaticField);

    case DuneShelter:
      return isUnlocked (BuildingSandNest);

    case Mines:
      return isUnlocked (BuildingMines);

    case GlassNests:
      return isUnlocked (RessourceGlass);

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
      return isUnlocked (RessourceFood);

    case Sand:
      return true;

    case Stone:
      return isUnlocked (JobMining);

    case Insight:
      return isUnlocked (FocusingUpgradeBought);

    case Glass:
      return isUnlocked (RessourceGlass);

    case StoneSlab:
      return isUnlocked (RessourceStoneSlab);

    case GlassPane:
      return isUnlocked (RessourceGlassPane);

    default:
      return true;
    }
}

bool
AchievementSystem::isUnlocked (AbilityType t) const
{
  using enum AbilityType;
  switch (t)
    {
    case AbilityLightning:
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