#include "AchievementDataView.hpp"
#include "AchievementIDs.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "UpgradeId.hpp"

// TODO : This file contains a mapping of some achievements to types, move the
// functions to the class responsible for the achievements

AchievementDataView::AchievementDataView (std::shared_ptr<AchievementSystem> a)
    : achievements (a)
{
}

bool
AchievementDataView::isUnlocked (AchievementIDs id) const
{
  return achievements->isUnlocked (id);
}

bool
AchievementDataView::isUnlocked (BuildingType t) const
{
  using enum BuildingType;
  switch (t)
    {
    case PlanktonField:
      return achievements->isUnlocked (AchievementIDs::PlanktonField);

    case DuneShelter:
      return achievements->isUnlocked (AchievementIDs::FirstSandNest);

    case Mines:
      return achievements->isUnlocked (AchievementIDs::Mines);

    default:
      return false;
    }
}

bool
AchievementDataView::isUnlocked (JellyJobs j) const
{
  using enum JellyJobs;
  switch (j)
    {
    case GatherSand:
      return achievements->isUnlocked (AchievementIDs::FirstJelly);

    case ExploreTheDepths:
      return achievements->isUnlocked (AchievementIDs::JobExploreTheDepths);

    case FocusForInsight:
      return achievements->isUnlocked (AchievementIDs::FocusingUpgradeBought);

    case Mining:
      return achievements->isUnlocked (AchievementIDs::JobMining);

    default:
      return false;
    }
}

bool
AchievementDataView::isUnlocked (RessourceType r) const
{

  switch (r)
    {
      using enum AchievementIDs;
      using enum RessourceType;

    case Food:
      return true;

    case Sand:
      return achievements->isUnlocked (FirstJelly);

    case Stone:
      return achievements->isUnlocked (JobMining);

    case Insight:
      return achievements->isUnlocked (FocusingUpgradeBought);

    case Glass:
      return achievements->isUnlocked (LightningAbilityBuyable);

    default:
      return false;
    }
}

bool
AchievementDataView::isUnlocked (AbilityType t) const
{
  using enum AbilityType;
  switch (t)
    {
    case CallThunder:
      return achievements->isUnlocked (
          AchievementIDs::LightningAbilityBuyable);
    }
}

bool
AchievementDataView::isUnlocked (UpgradeID id) const
{
  using enum UpgradeID;
  switch (id)
    {
    case Focusing:
      return achievements->isUnlocked (AchievementIDs::AncientOctopus);

    case Telekinesis:
      return achievements->isUnlocked (AchievementIDs::FocusingUpgradeBought);

    case AdvancedTelekinesis:
      return achievements->isUnlocked (
          AchievementIDs::TelekinesisUpgradeBought);

    case Writing:
      return achievements->isUnlocked (
          AchievementIDs::AdvancedTelekinesisUpgradeBought);

    default:
      return false;
    }
}