#include "Building.hpp"
#include "gtest/gtest.h"

TEST (TestsBuildings, initialization)
{
  Building b (BuildingType::DuneShelter);
  ASSERT_EQ (0, b.getCurrentQuantity ());
}
