#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <set>

TEST (jsonTests, BuildingFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::BuildingsPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class BuildingJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::BuildingsPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (BuildingJson_Fixture, NoNegativeOrNeutralPriceMultiplier)
{
  for (const auto &building : json.at ("Buildings"))
    {
      ASSERT_GE (building.at ("PriceMultiplier"), 1);
    }
}

TEST_F (BuildingJson_Fixture, IDUniqueness)
{
  std::set<BuildingType> idSet;

  for (const auto &building : json.at ("Buildings"))
    {
      const BuildingType id (building.at ("BuildingID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}
