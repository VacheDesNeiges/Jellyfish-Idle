#include "CraftingManager.hpp"
#include "CraftingRecipe.hpp"
#include "FilePaths.hpp"
#include "gtest/gtest.h"

class CraftingRecipes_Fixture : public ::testing::Test
{
  public:
    std::vector<CraftingRecipe> recipes;
    void SetUp() override
    {
        auto fstream = FilePaths::getFileStream(FilePaths::RecipesPath);
        auto json = nlohmann::json::parse(fstream);
        for (const auto &recipe : json.at("Recipes"))
        {
            recipes.emplace_back(recipe);
        }
    }
};

TEST_F(CraftingRecipes_Fixture, initialization)
{
    for (const auto &recipe : recipes)
    {
        ASSERT_FALSE(recipe.isDone());
        ASSERT_FALSE(recipe.isOngoing());
        ASSERT_EQ(1, recipe.getRecipelvl());
    }
}

TEST_F(CraftingRecipes_Fixture, duringCraft)
{
    for (auto &recipe : recipes)
    {
        const auto requiredTicks = recipe.getTotalRequiredTicks();
        ASSERT_LT(1, requiredTicks);
        ASSERT_FALSE(recipe.isOngoing());
        ASSERT_FALSE(recipe.isDone());
        recipe.start();
        ASSERT_TRUE(recipe.isOngoing());
        ASSERT_FALSE(recipe.isDone());
    }
}

TEST_F(CraftingRecipes_Fixture, ticks)
{
    for (auto &c : recipes)
    {
        const auto x = c.getTotalRequiredTicks();
        c.start();

        for (unsigned i = 1; i < c.getTotalRequiredTicks(); i++)
        {
            c.tick();
            ASSERT_EQ(x - i, c.getRemainingTicks());
            ASSERT_TRUE(c.isOngoing());
            ASSERT_FALSE(c.isDone());
        }
        c.tick();
        ASSERT_EQ(0, c.getRemainingTicks());
        ASSERT_FALSE(c.isOngoing());
        ASSERT_TRUE(c.isDone());
    }
}

TEST_F(CraftingRecipes_Fixture, cancel)
{
    for (auto &c : recipes)
    {
        const auto x = c.getTotalRequiredTicks();
        c.start();
        c.tick();
        c.cancel();
        ASSERT_EQ(x, c.getRemainingTicks());
        ASSERT_FALSE(c.isOngoing());
        ASSERT_FALSE(c.isDone());
    }
}

class CraftingManagerFixture : public ::testing::Test
{
  public:
    CraftingManager cManager;
};

TEST_F(CraftingManagerFixture, initialization)
{
    for (const auto &recipeID : cManager.getRecipeTypes())
    {
        ASSERT_EQ(0, cManager.getAssignedNumOfJellies(recipeID));
        ASSERT_EQ(false, cManager.craftIsOngoing(recipeID));
    }
}
