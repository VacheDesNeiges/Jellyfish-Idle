#include "Achievement.hpp"
#include "gtest/gtest.h"

TEST (TestsAchievements, initialization)
{
  Achievement a;
  ASSERT_EQ (a.isUnlocked (), false);
}

TEST (TestsAchievements, unlocking)
{
  Achievement a;
  a.unlock ();
  ASSERT_EQ (a.isUnlocked (), true);
}

TEST (TestsAchievements, settingState)
{
  Achievement a;
  a.setState (true);
  ASSERT_EQ (a.isUnlocked (), true);
  a.setState (false);
  ASSERT_EQ (a.isUnlocked (), false);
}