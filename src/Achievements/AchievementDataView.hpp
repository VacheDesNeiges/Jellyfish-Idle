#pragma once
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include <memory>

class AchievementDataView
{
public:
  explicit AchievementDataView (std::shared_ptr<AchievementSystem>);

  bool isUnlocked (BuildingType) const;
  bool isUnlocked (JellyJobs) const;
  bool isUnlocked (AchievementIDs) const;
  bool isUnlocked (RessourceType) const;
  bool isUnlocked (AbilityType) const;

private:
  std::shared_ptr<AchievementSystem> achievements;
};