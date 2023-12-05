#include "AchievementSystem.hpp"
#include "Achievement.hpp"
#include <utility>
#include <vector>

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

std::vector<std::pair<AchievementIDs, bool> >
AchievementSystem::getData () const
{
  std::vector<std::pair<AchievementIDs, bool> > result;

  for (const auto &[id, val] : achievements)
    {
      result.emplace_back (id, val.isUnlocked ());
    }
  return result;
}

void
AchievementSystem::loadData (
    const std::vector<std::pair<AchievementIDs, bool> > &data)
{
  for (const auto &[id, unlockedState] : data)
    {
      achievements[id].setState (unlockedState);
    }
}