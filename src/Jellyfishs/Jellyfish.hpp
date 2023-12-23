#pragma once

#include <array>
enum class JellyJobs
{
  None,
  GatherFood,
  GatherSand,
  ExploreTheDepths,
  Mining,
  FocusForInsight,
  Last
};

class Jellyfish
{
public:
  void setJob (JellyJobs);
  void gainJobExp (unsigned);
  JellyJobs getJob () const;

  static constexpr std::array<JellyJobs, 6> JobsTypes = {
    JellyJobs::None,   JellyJobs::GatherFood,       JellyJobs::GatherSand,
    JellyJobs::Mining, JellyJobs::ExploreTheDepths, JellyJobs::FocusForInsight
  };

private:
  unsigned id = 0;
  JellyJobs currentJob = JellyJobs::None;

  unsigned GatheringFoodLvl = 0;
  unsigned long GatheringFoodExp = 0;

  unsigned GatheringSandLevel = 0;
  unsigned long GatheringSandExp = 0;

  unsigned exploreTheDepthsLvl = 0;
  unsigned long exploreTheDepthsExp = 0;

  unsigned miningLvl = 0;
  unsigned long miningLvlExp = 0;
};