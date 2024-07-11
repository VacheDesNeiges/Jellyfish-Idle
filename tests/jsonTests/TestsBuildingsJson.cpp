#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <nlohmann/detail/value_t.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <set>

TEST (jsonTests, BuildingFileCanBeRead)
{
  const auto path = std::string (FilePaths::getPath ())
                    + std::string (FilePaths::BuildingsPath);

  std::fstream fstream (path);
  ASSERT_NO_THROW (nlohmann::json json = nlohmann::json::parse (fstream));
}

class BuildingJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    const auto path = std::string (FilePaths::getPath ())
                      + std::string (FilePaths::BuildingsPath);

    std::fstream fstream (path);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (BuildingJson_Fixture, HasAllRequiredFields)
{
  for (const auto &building : json.at ("Buildings"))
    {
      ASSERT_TRUE (building.contains ("BuildingID"));
      ASSERT_TRUE (building.contains ("Description"));
      ASSERT_TRUE (building.contains ("IncreaseToJfish"));
      ASSERT_TRUE (building.contains ("PriceMultiplier"));
      ASSERT_TRUE (building.contains ("BasePrice"));
    }
}

TEST_F (BuildingJson_Fixture, ValuesHaveCorrectTypes)
{
  for (const auto &building : json.at ("Buildings"))
    {
      ASSERT_EQ (building.at ("BuildingID").type (),
                 nlohmann::detail::value_t::number_unsigned);

      ASSERT_EQ (building.at ("Name").type (),
                 nlohmann::detail::value_t::string);

      ASSERT_EQ (building.at ("Description").type (),
                 nlohmann::detail::value_t::string);

      ASSERT_EQ (building.at ("IncreaseToJfish").type (),
                 nlohmann::detail::value_t::number_unsigned);

      ASSERT_TRUE (building.at ("PriceMultiplier").type ()
                       == nlohmann::detail::value_t::number_float
                   || building.at ("PriceMultiplier").type ()
                          == nlohmann::detail::value_t::number_unsigned);

      for (const auto &basePrice : building.at ("BasePrice"))
        {
          ASSERT_EQ (basePrice.at ("RessourceID").type (),
                     nlohmann::detail::value_t::number_unsigned);

          ASSERT_EQ (basePrice.at ("Quantity").type (),
                     nlohmann::detail::value_t::number_unsigned);
        }
    }
}

TEST_F (BuildingJson_Fixture, NoNegativeOrNeutralPriceMultiplier)
{
  for (const auto &building : json.at ("Buildings"))
    {
      ASSERT_FALSE (building.at ("PriceMultiplier") <= 1);
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
