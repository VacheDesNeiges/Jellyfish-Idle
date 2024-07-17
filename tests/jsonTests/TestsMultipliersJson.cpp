#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <set>

TEST (jsonTests, MultipliersFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::MultipliersPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class MultipliersJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::MultipliersPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (MultipliersJson_Fixture, IDUniqueness)
{
  std::set<MultiplierID> idSet;

  for (const auto &multiplier : json.at ("Multipliers"))
    {
      const MultiplierID id (multiplier.at ("ID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}