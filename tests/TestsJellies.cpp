#include "GameDataView.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "gtest/gtest.h"
#include <array>

TEST (TestsJellies, initialization)
{
  Jellyfish j;
  ASSERT_EQ (JellyJobs::None, j.getJob ());
}

TEST (TestsJellies, settingJob)
{
  Jellyfish j;
  for (const auto &job : Jellyfish::JobsTypes)
    {
      j.setJob (job);
      ASSERT_EQ (job, j.getJob ());
    }
}

TEST (TestsJelliesManager, initialization)
{
  JellyfishManager manager;
  ASSERT_EQ (0, manager.getNumJellies ());
  ASSERT_EQ (1, manager.getMaxNumJellies ());
  for (const auto &job : Jellyfish::JobsTypes)
    {
      ASSERT_EQ (0, manager.getNum (job));
    }
}

TEST (TestsJelliesManager, jelliesCreation)
{
  JellyfishManager manager;
  manager.createJellyfish ();
  ASSERT_EQ (1, manager.getNumJellies ());
}

TEST (TestsJelliesManager, overflow)
{
  JellyfishManager manager;
  manager.createJellyfish ();
  manager.createJellyfish ();
  manager.createJellyfish ();

  ASSERT_EQ (1, manager.getMaxNumJellies ());
  ASSERT_EQ (1, manager.getNumJellies ());
}

TEST (TestsJelliesManager, jobAssignement)
{
  JellyfishManager manager;

  for (const auto &job : Jellyfish::JobsTypes)
    {
      if (job != JellyJobs::None)
        {
          manager.createJellyfish ();
          manager.assign (job);
          ASSERT_EQ (1, manager.getNum (job));
        }
    }
}

TEST (TestsJelliesManager, jobUnasignement)
{
  JellyfishManager manager;
  manager.createJellyfish ();
  ASSERT_EQ (1, manager.getNum (JellyJobs::None));

  for (const auto &job : Jellyfish::JobsTypes)
    {
      if (job != JellyJobs::None)
        {
          manager.assign (job);
          manager.unasign (job);
          ASSERT_EQ (0, manager.getNum (job));
          ASSERT_EQ (1, manager.getNum (JellyJobs::None));
        }
    }
}