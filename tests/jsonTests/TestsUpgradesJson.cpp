#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <set>

TEST (jsonTests, UpgradesFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::UpgradesPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class UpgradesJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::UpgradesPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (UpgradesJson_Fixture, IDUniqueness)
{
  std::set<UpgradeID> idSet;

  for (const auto &upgrade : json.at ("Upgrades"))
    {
      const UpgradeID id (upgrade.at ("ID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}
TEST_F (UpgradesJson_Fixture, abherantValue)
{
  for (const auto &upgrade : json.at ("Upgrades"))
    {
      for (const auto &cost : upgrade.at ("Cost"))
        {
          ASSERT_GT (cost.at ("Quantity"), 0);
          ASSERT_GT (cost.at ("RessourceID"), 0);
        }
    }
}