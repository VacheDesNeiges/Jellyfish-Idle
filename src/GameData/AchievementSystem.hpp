#pragma once

#include "Achievement.hpp"
#include <map>
class AchievementSystem
{
public:
  AchievementSystem ();
  bool isUnlocked (AchievementIDs);
  void unlock (AchievementIDs);

private:
  std::map<AchievementIDs, Achievement> achievements;
};