#include "Building.hpp"
#include "BuildingManager.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"
#include <cstddef>
#include <vector>

class BuildingTests_Fixture : public ::testing::Test
{
public:
  std::vector<Building> buildings;
  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::BuildingsPath);
    auto json = nlohmann::json::parse (fstream);

    for (const auto &building : json.at ("Buildings"))
      {
        buildings.emplace_back (building);
      }
  }
};

TEST_F (BuildingTests_Fixture, initialization)
{
  for (const auto &building : buildings)
    {
      ASSERT_EQ (0, building.getCurrentQuantity ());
    }
}

TEST_F (BuildingTests_Fixture, buying)
{
  for (auto &building : buildings)
    {
      building.buy ();
      ASSERT_EQ (1, building.getCurrentQuantity ());
    }
}

TEST_F (BuildingTests_Fixture, setQuantity)
{
  for (auto &building : buildings)
    {
      building.setQuantity (50000);
      ASSERT_EQ (50000, building.getCurrentQuantity ());
      building.buy ();
      ASSERT_EQ (50001, building.getCurrentQuantity ());
      building.setQuantity (5);
      ASSERT_EQ (5, building.getCurrentQuantity ());
    }
}

TEST_F (BuildingTests_Fixture, hasName)
{
  for (const auto &building : buildings)
    {
      ASSERT_GT (building.getBuildingName ().size (), 0);
    }
}

TEST_F (BuildingTests_Fixture, hasDescription)
{
  for (const auto &building : buildings)
    {
      ASSERT_GT (building.getDescription ().size (), 0);
    }
}

TEST (TestsBuildingManager, initialization)
{
  BuildingManager bManager;
  for (const auto &building : bManager.getBuildingTypes ())
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
  for (const auto &building : bManager.getBuildingTypes ())
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

  for (const auto &building : bManager.getBuildingTypes ())
    {
      if (building == BuildingsAlias::DUNESHELTER
          || building == BuildingsAlias::GLASSNESTS)
        {
          ASSERT_EQ (true, bManager.doesIncreasesMaxJellies (building));
        }
      else
        {
          ASSERT_EQ (false, bManager.doesIncreasesMaxJellies (building));
        }
    }
}

TEST (TestsBuildingManager, costIncreaseOnBuy)
{
  BuildingManager bManager;

  for (const auto &building : bManager.getBuildingTypes ())
    {
      const auto &initialCost = bManager.nextBuyCost (building);
      bManager.buy (building);
      const auto &nextCost = bManager.nextBuyCost (building);

      for (size_t i = 0; i < initialCost.size (); i++)
        {
          ASSERT_GT (nextCost.at (i).second, initialCost.at (i).second);
        }
    }
}

TEST (TestsBuildingManager, ConsumptionIsZeroWhenNoBuildings)
{
  BuildingManager bManager;

  for (const auto &[rType, quantity] : bManager.getConsumptionRates ())
    {
      ASSERT_EQ (0, quantity);
    }
}