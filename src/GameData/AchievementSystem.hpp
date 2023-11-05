#pragma once

#include "Achievement.hpp"
#include <map>
#include <vector>

class AchievementSystem
{
public:
  AchievementSystem ();
  bool isUnlocked (AchievementIDs);
  void unlock (AchievementIDs);
  std::vector<std::pair<AchievementIDs, bool> > getData () const;

private:
  std::map<AchievementIDs, Achievement> achievements;
};