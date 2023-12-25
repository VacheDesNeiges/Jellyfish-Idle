#include "Achievement.hpp"
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