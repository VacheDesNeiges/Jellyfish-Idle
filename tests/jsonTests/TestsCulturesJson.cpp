#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

TEST (jsonTests, CulturesFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::CulturesPath);
  ASSERT_NO_THROW (const auto json = nlohmann::json::parse (fstream));
}

class CulturesJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::CulturesPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (CulturesJson_Fixture, IDUniqueness)
{
  std::set<AquaCultureID> idSet;
  for (const auto &culture : json.at ("Cultures"))
    {
      const AquaCultureID id (culture.at ("ID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}