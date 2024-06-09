#include "AquaCulture.hpp"
#include "AquaCultureID.hpp"
#include "GardenManager.hpp"
#include "gtest/gtest.h"

class AquaCultureFixture : public ::testing::Test
{
public:
  AquaCulture ac{ AquaCultureID::Plankton };
};

TEST_F (AquaCultureFixture, initialization) { ASSERT_FALSE (ac.isOngoing ()); }

TEST_F (AquaCultureFixture, whenOngoing)
{
  ASSERT_FALSE (ac.isOngoing ());
  ac.start ();
  ASSERT_TRUE (ac.isOngoing ());
}

TEST_F (AquaCultureFixture, cancel)
{
  ac.start ();
  ac.cancel ();
  ASSERT_FALSE (ac.isOngoing ());
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