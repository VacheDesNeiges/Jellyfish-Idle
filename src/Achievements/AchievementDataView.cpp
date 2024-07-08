#include "AchievementDataView.hpp"

#include "AchievementSystem.hpp"
#include "AquaCultureID.hpp"
#include "UpgradeId.hpp"
#include <optional>
#include <string_view>

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
AchievementDataView::isUnlocked (JellyJob j) const
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

bool
AchievementDataView::isUnlocked (AquaCultureID id) const
{
  return achievements->isUnlocked (id);
}

std::optional<std::string_view>
AchievementDataView::getNextNotification () const
{
  return achievements->getNotification ();
}