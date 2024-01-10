#pragma once

#include "Achievement.hpp"
#include "GameDataAccess.hpp"
#include "SaveAndLoadable.hpp"
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
  bool isUnlocked (AchievementIDs);
  void unlock (AchievementIDs);
  std::vector<std::pair<AchievementIDs, bool> > getData () const override;
  void
  loadData (const std::vector<std::pair<AchievementIDs, bool> > &) override;
  void checkAchievements ();

private:
  std::unordered_map<AchievementIDs, Achievement> achievements;
  std::unordered_map<AchievementIDs, std::function<bool ()> >
      achievementConditions;
};