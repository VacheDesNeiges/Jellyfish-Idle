#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <set>

TEST (jsonTests, AbilityFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::AbilitiesPath);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class AbilitiesJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::AbilitiesPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (AbilitiesJson_Fixture, IDUniqueness)
{
  std::set<AbilityType> idSet;

  for (const auto &ability : json.at ("Ability"))
    {
      const AbilityType id (ability.at ("ID"));
      ASSERT_FALSE (idSet.contains (id));
      idSet.insert (id);
    }
}

TEST_F (AbilitiesJson_Fixture, abherantValues)
{
  for (const auto &ability : json.at ("Ability"))
    {
      ASSERT_NE (0, ability.at ("ID"));

      for (const auto &cost : ability.at ("Cost"))
        {
          ASSERT_GT (cost.at ("RessourceID"), 0);
          ASSERT_GT (cost.at ("Quantity"), 0);
        }

      for (const auto &effect : ability.at ("Effect"))
        {
          ASSERT_GT (effect.at ("RessourceID"), 0);
          ASSERT_GT (effect.at ("Quantity"), 0);
        }
    }
}