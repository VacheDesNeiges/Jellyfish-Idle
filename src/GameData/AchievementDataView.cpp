#include "AchievementDataView.hpp"
#include "AchievementSystem.hpp"

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

    case SandNest:
      return achievements->isUnlocked (AchievementIDs::FirstSandNest);

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
      return achievements->isUnlocked (AchievementIDs::JobFocusing);

    default:
      return false;
    }
}

bool
AchievementDataView::isUnlocked (RessourceType r) const
{

  switch (r)
    {
      using enum RessourceType;

    case Food:
      return true;

    case Sand:
      return achievements->isUnlocked (AchievementIDs::FirstJelly);

    case Insight:
      return achievements->isUnlocked (AchievementIDs::JobFocusing);

    case Glass:
      return achievements->isUnlocked (AchievementIDs::FirstInsightAbility);

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
      return achievements->isUnlocked (AchievementIDs::FirstInsightAbility);
    }
}
