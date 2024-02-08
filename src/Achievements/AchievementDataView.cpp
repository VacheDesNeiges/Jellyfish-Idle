#include "AchievementDataView.hpp"

#include "AchievementIDs.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "UpgradeId.hpp"

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
  return achievements->isUnlocked (t);
}

bool
AchievementDataView::isUnlocked (JellyJobs j) const
{
  return achievements->isUnlocked (j);
}

bool
AchievementDataView::isUnlocked (RessourceType r) const
{
  return achievements->isUnlocked (r);
}

bool
AchievementDataView::isUnlocked (AbilityType t) const
{
  return achievements->isUnlocked (t);
}

bool
AchievementDataView::isUnlocked (UpgradeID id) const
{
  return achievements->isUnlocked (id);
}