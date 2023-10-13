#pragma once

class Achievement
{
public:
  bool isUnlocked () const;
  void unlock ();

private:
  bool unlocked;
};

enum class AchievementIDs
{
  PlanktonField,
  Last
};