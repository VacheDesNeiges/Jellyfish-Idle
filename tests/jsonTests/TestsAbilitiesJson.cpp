#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"
#include <nlohmann/detail/value_t.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
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

TEST_F (AbilitiesJson_Fixture, HasAllRequiredFields)
{
  for (const auto &ability : json.at ("Ability"))
    {
      ASSERT_TRUE (ability.contains ("ID"));
      ASSERT_TRUE (ability.contains ("Name"));
      ASSERT_TRUE (ability.contains ("Description"));

      ASSERT_TRUE (ability.contains ("Cost"));
      for (const auto &cost : ability.at ("Cost"))
        {
          ASSERT_TRUE (cost.contains ("RessourceID"));
          ASSERT_TRUE (cost.contains ("Quantity"));
        }

      ASSERT_TRUE (ability.contains ("Effect"));
      for (const auto &effect : ability.at ("Effect"))
        {
          ASSERT_TRUE (effect.contains ("RessourceID"));
          ASSERT_TRUE (effect.contains ("Quantity"));
        }
    }
}

TEST_F (AbilitiesJson_Fixture, ValuesHaveCorrectTypes)
{
  using nlohmann::detail::value_t;
  for (const auto &ability : json.at ("Ability"))
    {
      ASSERT_EQ (ability.at ("ID").type (), value_t::number_unsigned);
      ASSERT_EQ (ability.at ("Name").type (), value_t::string);
      ASSERT_EQ (ability.at ("Description").type (), value_t::string);

      for (const auto &cost : ability.at ("Cost"))
        {
          ASSERT_EQ (cost.at ("RessourceID").type (),
                     value_t::number_unsigned);
          ASSERT_EQ (cost.at ("Quantity").type (), value_t::number_unsigned);
        }

      for (const auto &effect : ability.at ("Effect"))
        {
          ASSERT_EQ (effect.at ("RessourceID").type (),
                     value_t::number_unsigned);
          ASSERT_EQ (effect.at ("Quantity").type (), value_t::number_unsigned);
        }
    }
}

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