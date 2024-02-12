#include "CraftingRecipe.hpp"
#include "RecipeID.hpp"

#include <cassert>
#include <cmath>

CraftingRecipe::CraftingRecipe (RecipeID id)
{
  switch (id)
    {
      using enum RessourceType;

    case RecipeID::StoneSlabRecipe:
      recipeName = "Stone Slab";
      baseTicksForCraft = 120;
      recipe.emplace_back (Stone, 5);
      baseResult.emplace_back (StoneSlab, 1);
      break;

    case RecipeID::GlassPanelRecipe:
      recipeName = "Glass Pane";
      baseTicksForCraft = 300;
      recipe.emplace_back (Glass, 100);
      baseResult.emplace_back (GlassPane, 1);
      break;

    default:
      assert (false);
    }
  remainingTicksToCraft = baseTicksForCraft;
  level = { 1, 0, 100 };
}

void
CraftingRecipe::start ()
{
  craftOngoing = true;
  remainingTicksToCraft = baseTicksForCraft;
}

void
CraftingRecipe::cancel ()
{
  craftOngoing = false;
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
  if (craftOngoing)
    {
      remainingTicksToCraft--;
      if (remainingTicksToCraft == 0)
        {
          craftOngoing = false;
          done = true;
          level.currentProgress += 10; // Have the base xp values be global
                                       // constexpr in their own file
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

bool
CraftingRecipe::isOngoing () const
{
  return craftOngoing;
}

void
CraftingRecipe::reset ()
{
  done = false;
  craftOngoing = false;
  remainingTicksToCraft = baseTicksForCraft;
}

unsigned
CraftingRecipe::getRecipelvl () const
{
  return level.lvl;
}

bool
CraftingRecipe::applyExp ()
{
  bool hasLeveledUp = false;
  while (level.currentProgress >= level.progressNeeded)
    {
      hasLeveledUp = true;
      level.lvl += 1;
      level.currentProgress -= level.progressNeeded;
      level.progressNeeded
          = 10 * level.lvl * (level.lvl / std::log (level.lvl));
    }
  return hasLeveledUp;
}

RecipeLevel
CraftingRecipe::getLevelData () const
{
  return level;
}

RecipeSaveData
CraftingRecipe::getData () const
{
  RecipeSaveData result;
  result.craftDone = done;
  result.craftOngoing = craftOngoing;
  result.remainingTicksToCraft = remainingTicksToCraft;
  result.lvl = level.lvl;
  result.currentProgress = level.currentProgress;
  result.progressNeeded = level.progressNeeded;

  return result;
}

void
CraftingRecipe::loadData (const RecipeSaveData &data)
{
  done = data.craftDone;
  craftOngoing = data.craftOngoing;
  remainingTicksToCraft = data.remainingTicksToCraft;
  level.lvl = data.lvl;
  level.currentProgress = data.currentProgress;
  level.progressNeeded = data.progressNeeded;
}