#include "Building.hpp"
#include "BuildingManager.hpp"
#include "gtest/gtest.h"

/*

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

// FIXME Move to another more advanced test that init the gamedataview
TEST (TestsBuildingManager, initialization)
{
  BuildingManager bManager;
  for (const auto &building : Building::BuildingTypes)
    {
      ASSERT_EQ (0, bManager.getCurrentQuantity (building));
       for (const auto &[res, quant] : bManager.getProduction (building))
         {
           ASSERT_EQ (0, quant);
         }

}

  for (const auto &[res, quant] : bManager.getProductionRates ())
    {
      ASSERT_EQ (0, quant);
    }

}

TEST (TestsBuildingManager, buy)
{
BuildingManager bManager;
for (const auto &building : Building::BuildingTypes)
  {
    for (auto i = 0; i < 10; i++)
      {
        bManager.buy (building);
        ASSERT_EQ (i + 1, bManager.getCurrentQuantity (building));
      }
  }
}

TEST (TestsBuildingManager, increaseToJfish)
{
BuildingManager bManager;

for (const auto &building : Building::BuildingTypes)
  {
    if (building == BuildingType::DuneShelter
        || building == BuildingType::GlassNests)
      {
        ASSERT_EQ (true, bManager.doesIncreasesMaxJellies (building));
      }
    else
      {
        ASSERT_EQ (false, bManager.doesIncreasesMaxJellies (building));
      }
  }
}

*/