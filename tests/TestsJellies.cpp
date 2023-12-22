#include "Jellyfish.hpp"
#include "gtest/gtest.h"
#include <array>

TEST (TestsJellies, initialization)
{
  Jellyfish j;
  ASSERT_EQ (j.getJob (), JellyJobs::None);
}

TEST (TestsJellies, settingJob)
{
  Jellyfish j;
  for (const auto &job : Jellyfish::JobsTypes)
    {
      j.setJob (job);
      ASSERT_EQ (j.getJob (), job);
    }
}