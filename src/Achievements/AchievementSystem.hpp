#pragma once

#include "Achievement.hpp"
#include "Building.hpp"
#include "GameDataAccess.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "SaveAndLoadable.hpp"
#include "UpgradeId.hpp"

#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

class AchievementSystem
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<AchievementIDs, bool> > >
{
public:
  AchievementSystem ();
  ~AchievementSystem () override = default;

  bool isUnlocked (AchievementIDs) const;
  bool isUnlocked (BuildingType) const;
  bool isUnlocked (JellyJobs) const;
  bool isUnlocked (RessourceType) const;
  bool isUnlocked (AbilityType) const;
  bool isUnlocked (UpgradeID) const;

  void unlock (AchievementIDs);
  std::vector<std::pair<AchievementIDs, bool> > getData () const override;
  void
  loadData (const std::vector<std::pair<AchievementIDs, bool> > &) override;
  void checkAchievements ();

private:
  void initLambdas ();
  std::unordered_map<AchievementIDs, Achievement> achievements;
  std::unordered_map<AchievementIDs, std::function<bool ()> >
      achievementConditions;
};