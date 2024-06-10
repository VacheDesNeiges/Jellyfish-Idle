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
  Artisan
};

class Jellyfish
{
public:
  void setJob (JellyJobs);
  void gainJobExp (unsigned);
  JellyJobs getJob () const;

  static constexpr std::array<JellyJobs, 7> JobsTypes = {
    JellyJobs::None,
    JellyJobs::Mining,
    JellyJobs::ExploreTheDepths,
    JellyJobs::FocusForInsight,
    JellyJobs::Artisan,
  };

private:
  JellyJobs currentJob = JellyJobs::None;
};