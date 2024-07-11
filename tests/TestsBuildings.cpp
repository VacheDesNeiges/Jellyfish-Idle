#include "Building.hpp"
#include "BuildingManager.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "fstream"
#include "gtest/gtest.h"
#include <vector>

class BuildingTests_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;
  std::vector<Building> buildings;
  void
  SetUp () override
  {
    const auto path = std::string (FilePaths::getPath ())
                      + std::string (FilePaths::BuildingsPath);

    std::fstream fstream (path);
    json = nlohmann::json::parse (fstream);
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
