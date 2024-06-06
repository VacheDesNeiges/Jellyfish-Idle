#include "AquaCulture.hpp"
#include "AquaCultureID.hpp"
#include "GardenManager.hpp"
#include "gtest/gtest.h"
#include <cassert>

class AquaCultureFixture : public ::testing::Test
{
public:
  AquaCulture ac{ AquaCultureID::Plankton };
};

TEST_F (AquaCultureFixture, initialization)
{
  ASSERT_FALSE (ac.isDone ());
  ASSERT_FALSE (ac.isOngoing ());
}

TEST_F (AquaCultureFixture, whenOngoing)
{
  const auto reqTicks = ac.getTotalRequiredTicks ();
  ASSERT_LT (1, reqTicks);
  ASSERT_FALSE (ac.isOngoing ());
  ASSERT_FALSE (ac.isDone ());
  ac.start ();
  ASSERT_TRUE (ac.isOngoing ());
  ASSERT_FALSE (ac.isDone ());
}

TEST_F (AquaCultureFixture, ticks)
{
  const auto reqTicks = ac.getTotalRequiredTicks ();
  ac.start ();

  for (unsigned i = 1; i < ac.getTotalRequiredTicks (); i++)
    {
      ac.tick ();
      ASSERT_EQ (reqTicks - i, ac.getRemainingTicks ());
      ASSERT_TRUE (ac.isOngoing ());
      ASSERT_FALSE (ac.isDone ());
    }
  ac.tick ();
  ASSERT_EQ (0, ac.getRemainingTicks ());
  ASSERT_FALSE (ac.isOngoing ());
  ASSERT_TRUE (ac.isDone ());
}

TEST_F (AquaCultureFixture, cancel)
{
  const auto reqTicks = ac.getTotalRequiredTicks ();
  ac.start ();
  ac.tick ();
  ac.cancel ();
  ASSERT_EQ (reqTicks, ac.getRemainingTicks ());
  ASSERT_FALSE (ac.isOngoing ());
  ASSERT_FALSE (ac.isDone ());
}

class GardenManagerFixture : public ::testing::Test
{
public:
  GardenManager gManager;
};

TEST_F (GardenManagerFixture, initialization)
{
  for (const auto &cultureID : AquaCulture::CultureTypes)
    {
      ASSERT_EQ (false, gManager.isOngoing (cultureID));
    }
}