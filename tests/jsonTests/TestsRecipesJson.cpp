#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

TEST (jsonTests, RecipesFileCanBeRead)
{
  auto fstream = FilePaths::getFileStream (FilePaths::RecipesPath);
  ASSERT_NO_THROW (const auto &json = nlohmann::json::parse (fstream));
}

class RecipesJson_Fixture : public ::testing::Test
{
public:
  nlohmann::json json;

  void
  SetUp () override
  {
    auto fstream = FilePaths::getFileStream (FilePaths::RecipesPath);
    json = nlohmann::json::parse (fstream);
  }
};

TEST_F (RecipesJson_Fixture, reservedValue)
{
  for (const auto &recipe : json.at ("Recipes"))
    {
      ASSERT_NE (RecipeID (recipe.at ("ID")), RecipesAlias::NONE);
    }
}

TEST_F (RecipesJson_Fixture, IDUniqueness)
{
  std::set<RecipeID> idset;
  for (const auto &recipe : json.at ("Recipes"))
    {
      const RecipeID id (recipe.at ("ID"));
      ASSERT_FALSE (idset.contains (id));
      idset.insert (id);
    }
}

TEST_F (RecipesJson_Fixture, abherantValues)
{
  for (const auto &recipe : json.at ("Recipes"))
    {
      ASSERT_GE (recipe.at ("BaseTicksRequired"), 0);

      for (const auto &cost : recipe.at ("Cost"))
        {
          ASSERT_GT (cost.at ("RessourceID"), 0);
          ASSERT_GT (cost.at ("Quantity"), 0);
        }

      for (const auto &result : recipe.at ("Result"))
        {
          ASSERT_GT (result.at ("RessourceID"), 0);
          ASSERT_GT (result.at ("Quantity"), 0);
        }
    }
}