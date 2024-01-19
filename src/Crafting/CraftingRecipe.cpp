#include "CraftingRecipe.hpp"
#include "RecipeID.hpp"
#include <cassert>

CraftingRecipe::CraftingRecipe (RecipeID id)
{
  switch (id)
    {
      using enum RessourceType;

    case RecipeID::StoneSlabRecipe:
      recipeName = "Stone Slab";
      baseTicksForCraft = 600;
      recipe.emplace_back (Stone, 200);
      baseResult.emplace_back (StoneSlab, 1);
      break;

    case RecipeID::GlassPanelRecipe:
      recipeName = "Glass Pane";
      baseTicksForCraft = 600;
      recipe.emplace_back (Glass, 100);
      baseResult.emplace_back (GlassPane, 1);
      break;

    default:
      assert (false);
    }
}

void
CraftingRecipe::start ()
{
  crafting = true;
  remainingTicksToCraft = baseTicksForCraft;
}

void
CraftingRecipe::cancel ()
{
  crafting = false;
  remainingTicksToCraft = baseTicksForCraft;
}

unsigned
CraftingRecipe::getRemainingTicks () const
{
  return remainingTicksToCraft;
}

std::vector<std::pair<RessourceType, double> >
CraftingRecipe::getRecipe () const
{
  return recipe;
}

std::vector<std::pair<RessourceType, double> >
CraftingRecipe::getBaseResult () const
{
  return baseResult;
}

bool
CraftingRecipe::tick ()
{
  if (crafting)
    {
      remainingTicksToCraft--;
      if (remainingTicksToCraft == 0)
        {
          crafting = false;
          done = true;
        }
    }
  return done;
}

bool
CraftingRecipe::isDone () const
{
  return done;
}

unsigned
CraftingRecipe::getTotalRequiredTicks () const
{
  return baseTicksForCraft;
}

std::string
CraftingRecipe::getName () const
{
  return recipeName;
}