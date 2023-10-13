#include "AchievementSystem.hpp"
#include "Achievement.hpp"

AchievementSystem::AchievementSystem ()
{
  using enum AchievementIDs;
  for (auto a = static_cast<int> (PlanktonField); a != static_cast<int> (Last);
       a++)
    {
      achievements.emplace (static_cast<AchievementIDs> (a), Achievement ());
    }
}

bool
AchievementSystem::isUnlocked (AchievementIDs id)
{
  return achievements[id].isUnlocked ();
}

void
AchievementSystem::unlock (AchievementIDs id)
{
  achievements[id].unlock ();
}