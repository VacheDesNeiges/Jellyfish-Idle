#pragma once
#include <memory>
#include <optional>

class AchievementSystem;
enum class RessourceType;
enum class BuildingType;
enum class JellyJobs;
enum class AchievementIDs;
enum class AbilityType;
enum class UpgradeID;
enum class AquaCultureID;

class AchievementDataView
{
public:
  explicit AchievementDataView (std::shared_ptr<AchievementSystem>);

  bool isUnlocked (BuildingType) const;
  bool isUnlocked (JellyJobs) const;
  bool isUnlocked (AchievementIDs) const;
  bool isUnlocked (RessourceType) const;
  bool isUnlocked (AbilityType) const;
  bool isUnlocked (UpgradeID) const;
  bool isUnlocked (AquaCultureID) const;

  std::optional<std::string_view> getNextNotification () const;

private:
  std::shared_ptr<AchievementSystem> achievements;
};