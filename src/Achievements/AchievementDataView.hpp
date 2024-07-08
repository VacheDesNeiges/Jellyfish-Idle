#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <optional>
#include <string_view>

class AchievementSystem;
enum class UpgradeID;
enum class AquaCultureID;

class AchievementDataView
{
public:
  explicit AchievementDataView (std::shared_ptr<AchievementSystem>);

  bool isUnlocked (BuildingType) const;
  bool isUnlocked (JellyJob) const;
  bool isUnlocked (AchievementIDs) const;
  bool isUnlocked (RessourceType) const;
  bool isUnlocked (AbilityType) const;
  bool isUnlocked (UpgradeID) const;
  bool isUnlocked (AquaCultureID) const;

  std::optional<std::string_view> getNextNotification () const;

private:
  std::shared_ptr<AchievementSystem> achievements;
};