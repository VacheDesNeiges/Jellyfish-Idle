#pragma once

enum class JellyJobs
{
  None,
  GatherSand,
  ExploreTheSea,
  FocusForInsight,
  Last
};

class Jellyfish
{
public:
  void setJob (JellyJobs);
  void gainJobExp (unsigned);
  JellyJobs getJob () const;

private:
  unsigned id = 0;
  JellyJobs currentJob = JellyJobs::None;

  unsigned GatheringFoodLvl = 0;
  unsigned long GatheringFoodExp = 0;

  unsigned GatheringSandLevel = 0;
  unsigned long GatheringSandExp = 0;

  unsigned exploreTheSeaLvl = 0;
  unsigned long exploreTheSeaExp = 0;
};