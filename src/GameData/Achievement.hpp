#pragma once

class Achievement
{
public:
  bool isUnlocked () const;
  void unlock ();

private:
  bool unlocked = false;
};

enum class AchievementIDs
{
  PlanktonField,
  FirstSandNest,
  JobGatherSand,
  JobFocusing,
  JobExploreTheSea,
  Last
};