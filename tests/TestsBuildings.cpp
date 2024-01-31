#include "Building.hpp"
#include "gtest/gtest.h"

TEST (TestsBuildings, initialization)
{
  Building b (BuildingType::DuneShelter);
  ASSERT_EQ (0, b.getCurrentQuantity ());
}

TEST (TestsBuildings, buying)
{
  Building b (BuildingType::DuneShelter);
  b.buy ();
  ASSERT_EQ (1, b.getCurrentQuantity ());
}

TEST (TestsBuildings, setQuantity)
{
  Building b (BuildingType::DuneShelter);
  b.setQuantity (50000);
  ASSERT_EQ (50000, b.getCurrentQuantity ());
  b.buy ();
  ASSERT_EQ (50001, b.getCurrentQuantity ());
  b.setQuantity (5);
  ASSERT_EQ (5, b.getCurrentQuantity ());
}