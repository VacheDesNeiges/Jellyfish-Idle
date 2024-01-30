#include "CraftingRecipe.hpp"
#include "RecipeID.hpp"
#include "gtest/gtest.h"

TEST (CraftingRecipes, initialization)
{
  CraftingRecipe c (RecipeID::StoneSlabRecipe);
  ASSERT_FALSE (c.isDone ());
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_EQ (0, c.getRecipelvl ());
}

TEST (CraftingRecipes, duringCraft)
{
  CraftingRecipe c (RecipeID::StoneSlabRecipe);
  const auto x = c.getTotalRequiredTicks ();
  ASSERT_LT (1, x);
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_FALSE (c.isDone ());
  c.start ();
  ASSERT_TRUE (c.isOngoing ());
  ASSERT_FALSE (c.isDone ());
}

TEST (CraftingRecipe, ticks)
{
  CraftingRecipe c (RecipeID::StoneSlabRecipe);
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

TEST (CraftingRecipe, cancel)
{
  CraftingRecipe c (RecipeID::StoneSlabRecipe);
  const auto x = c.getTotalRequiredTicks ();
  c.start ();
  c.tick ();
  c.cancel ();
  ASSERT_EQ (x, c.getRemainingTicks ());
  ASSERT_FALSE (c.isOngoing ());
  ASSERT_FALSE (c.isDone ());
}