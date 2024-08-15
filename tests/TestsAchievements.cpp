#include "Achievement.hpp"
#include "AchievementSystem.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"

TEST(TestsAchievements, initialization)
{
    Achievement a;
    ASSERT_EQ(false, a.isUnlocked());
}

TEST(TestsAchievements, unlocking)
{
    Achievement a;
    a.unlock();
    ASSERT_EQ(true, a.isUnlocked());
}

TEST(TestsAchievements, settingState)
{
    Achievement a;
    a.setState(true);
    EXPECT_EQ(true, a.isUnlocked());
    a.setState(false);
    ASSERT_EQ(false, a.isUnlocked());
}

TEST(TestsAchievementSystem, initialization)
{
    AchievementSystem aSys;

    for (const auto ach : aSys.getAchievementsIDs())
    {
        ASSERT_EQ(false, aSys.isUnlocked(ach));
    }
}

TEST(TestsAchievementSystem, unlocking)
{
    AchievementSystem aSys;

    for (const auto ach : aSys.getAchievementsIDs())
    {
        aSys.unlock(ach);
        ASSERT_EQ(true, aSys.isUnlocked(ach));
    }
}
