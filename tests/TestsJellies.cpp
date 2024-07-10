#include "GameIDsTypes.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "gtest/gtest.h"

TEST (TestsJellies, initialization)
{
  Jellyfish j;
  ASSERT_EQ (JobsAlias::NONE, j.getJob ());
}

TEST (TestsJellies, settingJob)
{
  JellyfishManager manager;
  Jellyfish j;
  for (const auto &job : manager.getAllJobsTypes ())
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
  for (const auto &job : manager.getAllJobsTypes ())
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
  manager.setBonusMaxJellies (
      static_cast<unsigned> (manager.getAllJobsTypes ().size ()));

  for (const auto &job : manager.getAllJobsTypes ())
    {
      if (job != JobsAlias::NONE)
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
  manager.setBonusMaxJellies (
      static_cast<unsigned> (manager.getAllJobsTypes ().size ()));

  manager.createJellyfish ();
  ASSERT_EQ (1, manager.getNum (JobsAlias::NONE));

  for (const auto &job : manager.getAllJobsTypes ())
    {
      if (job != JobsAlias::NONE)
        {
          manager.assign (job);
          manager.unasign (job);
          ASSERT_EQ (0, manager.getNum (job));
          ASSERT_EQ (1, manager.getNum (JobsAlias::NONE));
        }
    }
}
