#pragma once

#include "Achievement.hpp"
#include "GameDataAccess.hpp"
#include <functional>
#include <map>
#include <vector>

class AchievementSystem : public GameDataAccess
{
public:
  AchievementSystem ();
  bool isUnlocked (AchievementIDs);
  void unlock (AchievementIDs);
  std::vector<std::pair<AchievementIDs, bool> > getData () const;
  void loadData (const std::vector<std::pair<AchievementIDs, bool> > &);
  void checkAchievements ();

private:
  std::map<AchievementIDs, Achievement> achievements;
  std::map<AchievementIDs, std::function<bool ()> > achievementConditions;
};