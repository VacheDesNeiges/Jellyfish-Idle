#pragma once
#include "AchievementIDs.hpp"

class Achievement
{
public:
  bool isUnlocked () const;
  void unlock ();
  void setState (bool);

private:
  bool unlocked = false;
};
