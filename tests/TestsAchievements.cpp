#include "Achievement.hpp"
#include "AchievementIDs.hpp"
#include "AchievementSystem.hpp"
#include "gtest/gtest.h"

TEST (TestsAchievements, initialization)
{
  Achievement a;
  ASSERT_EQ (false, a.isUnlocked ());
}

TEST (TestsAchievements, unlocking)
{
  Achievement a;
  a.unlock ();
  ASSERT_EQ (true, a.isUnlocked ());
}

TEST (TestsAchievements, settingState)
{
  Achievement a;
  a.setState (true);
  ASSERT_EQ (true, a.isUnlocked ());
  a.setState (false);
  ASSERT_EQ (false, a.isUnlocked ());
}

TEST (TestsAchievementSystem, initialization)
{
  AchievementSystem aSys;
  using enum AchievementIDs;

  for (auto a = static_cast<int> (PlanktonField); a != static_cast<int> (Last);
       a++)
    {
      const auto ach = static_cast<AchievementIDs> (a);
      ASSERT_EQ (false, aSys.isUnlocked (ach));
    }
}

TEST (TestsAchievementSystem, unlocking)
{
  AchievementSystem aSys;
  using enum AchievementIDs;

  for (auto a = static_cast<int> (PlanktonField); a != static_cast<int> (Last);
       a++)
    {
      const auto ach = static_cast<AchievementIDs> (a);
      aSys.unlock (ach);
      ASSERT_EQ (true, aSys.isUnlocked (ach));
    }
}
