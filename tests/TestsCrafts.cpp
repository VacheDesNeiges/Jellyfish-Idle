#include "CraftingManager.hpp"
#include "CraftingRecipe.hpp"
#include "gtest/gtest.h"
/*
class CraftingRecipesFixture : public ::testing::Test
{
public:
  CraftingRecipe c{};
};

TEST_F (CraftingRecipesFixture, initialization)
{
  ASSERT_FALSE (c.isDone ());
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_EQ (1, c.getRecipelvl ());
}

TEST_F (CraftingRecipesFixture, duringCraft)
{
  const auto x = c.getTotalRequiredTicks ();
  ASSERT_LT (1, x);
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_FALSE (c.isDone ());
  c.start ();
  ASSERT_TRUE (c.isOngoing ());
  ASSERT_FALSE (c.isDone ());
}

TEST_F (CraftingRecipesFixture, ticks)
{
  const auto x = c.getTotalRequiredTicks ();
  c.start ();

  for (unsigned i = 1; i < c.getTotalRequiredTicks (); i++)
    {
      c.tick ();
      ASSERT_EQ (x - i, c.getRemainingTicks ());
      ASSERT_TRUE (c.isOngoing ());
      ASSERT_FALSE (c.isDone ());
    }
  c.tick ();
  ASSERT_EQ (0, c.getRemainingTicks ());
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_TRUE (c.isDone ());
}

TEST_F (CraftingRecipesFixture, cancel)
{
  const auto x = c.getTotalRequiredTicks ();
  c.start ();
  c.tick ();
  c.cancel ();
  ASSERT_EQ (x, c.getRemainingTicks ());
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_FALSE (c.isDone ());
}

class CraftingManagerFixture : public ::testing::Test
{
public:
  CraftingManager cManager;
};

TEST_F (CraftingManagerFixture, initialization)
{
  for (const auto &recipeID : cManager.getRecipeTypes ())
    {
      ASSERT_EQ (0, cManager.getAssignedNumOfJellies (recipeID));
      ASSERT_EQ (false, cManager.craftIsOngoing (recipeID));
    }
}*/