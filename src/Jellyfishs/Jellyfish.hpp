#pragma once

enum class JellyJobs
{
  None,
  GatherFood,
  GatherSeaShell,
  Mining,
  Last
};

class Jellyfish
{
public:
  void setJob (JellyJobs);
  void gainJobExp (unsigned);
  JellyJobs getJob () const;

private:
  unsigned id;
  JellyJobs currentJob = JellyJobs::None;

  unsigned GatheringFoodLvl = 0;
  unsigned long GatheringFoodExp = 0;

  unsigned GatheringShellsLevel = 0;
  unsigned long GatheringShellExp = 0;

  unsigned MiningLvl = 0;
  unsigned long MiningExp = 0;
};