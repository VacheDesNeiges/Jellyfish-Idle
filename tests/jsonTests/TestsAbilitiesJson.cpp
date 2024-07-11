#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <set>

TEST (jsonTests, AbilityFileCanBeRead)
{
  const auto path = std::string (FilePaths::getPath ())
                    + std::string (FilePaths::AbilitiesPath);

  std::fstream fstream (path);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class AbilitiesJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    const auto path = std::string (FilePaths::getPath ())
                      + std::string (FilePaths::AbilitiesPath);

    std::fstream fstream (path);
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