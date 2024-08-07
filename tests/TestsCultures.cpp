#include "AquaCulture.hpp"
#include "GameIDsTypes.hpp"
#include "GardenManager.hpp"
#include "gtest/gtest.h"

class AquaCultureFixture : public ::testing::Test
{
public:
  AquaCulture ac;
};

TEST_F (AquaCultureFixture, initialization) { ASSERT_FALSE (ac.isOngoing ()); }

TEST_F (AquaCultureFixture, whenOngoing)
{
  EXPECT_FALSE (ac.isOngoing ());
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
  for (const auto &cultureID : gManager.getCultureTypes ())
    {
      ASSERT_EQ (false, gManager.isOngoing (cultureID));
    }
}

TEST_F (GardenManagerFixture, assignementsAndUnasignements)
{
  ASSERT_GT (gManager.getTotalFields (), 0);
  for (const auto &cultureID : gManager.getCultureTypes ())
    {
      for (size_t i = 0; i < gManager.getTotalFields (); i++)
        {
          gManager.assign (cultureID);
        }
      ASSERT_EQ (gManager.getAssignedFieldsToCulture (cultureID),
                 gManager.getTotalFields ());

      for (size_t i = 0; i < gManager.getTotalFields (); i++)
        {
          gManager.unnasign (cultureID);
        }
      ASSERT_EQ (gManager.getAssignedFieldsToCulture (cultureID), 0);
    }
}