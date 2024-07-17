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