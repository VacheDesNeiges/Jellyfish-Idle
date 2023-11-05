#pragma once

class Achievement
{
public:
  bool isUnlocked () const;
  void unlock ();
  void setState (bool);

private:
  bool unlocked = false;
};

enum class AchievementIDs
{
  PlanktonField,
  FirstSandNest,
  FirstJelly,
  JobFocusing,
  JobExploreTheSea,
  FirstInsightAbility,
  ResearchTabUnlocked,
  Last
};