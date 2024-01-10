#pragma once
#include <memory>

class AchievementSystem;
enum class BuildingType;
enum class JellyJobs;
enum class AchievementIDs;
enum class RessourceType;
enum class AbilityType;
enum class UpgradeID;

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

private:
  std::shared_ptr<AchievementSystem> achievements;
};