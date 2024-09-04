#include "AchievementDataView.hpp"

#include "AchievementSystem.hpp"
#include "GameIDsTypes.hpp"
#include <optional>
#include <string_view>

AchievementDataView::AchievementDataView(
    std::shared_ptr<AchievementSystem> achievementsSystem)
    : achievements(achievementsSystem)
{
}

bool AchievementDataView::isUnlocked(AchievementIDs id) const
{
    return achievements->isUnlocked(id);
}

bool AchievementDataView::isUnlocked(BuildingType bType) const
{
    return achievements->isUnlocked(bType);
}

bool AchievementDataView::isUnlocked(JellyJob bType) const
{
    return achievements->isUnlocked(bType);
}

bool AchievementDataView::isUnlocked(RessourceType rType) const
{
    return achievements->isUnlocked(rType);
}

bool AchievementDataView::isUnlocked(AbilityType abiType) const
{
    return achievements->isUnlocked(abiType);
}

bool AchievementDataView::isUnlocked(UpgradeID id) const
{
    return achievements->isUnlocked(id);
}

bool AchievementDataView::isUnlocked(AquaCultureID cultureID) const
{
    return achievements->isUnlocked(cultureID);
}

std::optional<std::string_view> AchievementDataView::getNextNotification() const
{
    return achievements->getNotification();
}

std::span<const std::tuple<AchievementIDs, unsigned, std::string, std::string>>
AchievementDataView::getDepthRewards() const
{
    return achievements->getDepthRewards();
}
