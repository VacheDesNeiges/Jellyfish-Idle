#include "CraftingManager.hpp"
#include "CraftingRecipe.hpp"
#include "RecipeID.hpp"
#include <utility>
#include <vector>

CraftingManager::CraftingManager ()
{
  for (const auto &c : CraftingRecipe::RecipeTypes)
    {
      recipes[c] = CraftingRecipe (c);
    }
}

bool
CraftingManager::assign (RecipeID id)
{
  if (assignedNumbersOfJellies[RecipeID::NoneRecipe] > 0)
    {
      assignedNumbersOfJellies[id]++;
      return true;
    }
  return false;
}

bool
CraftingManager::unasign (RecipeID id)
{
  if (assignedNumbersOfJellies[id] > 0)
    {
      assignedNumbersOfJellies[id]--;
      assignedNumbersOfJellies[RecipeID::NoneRecipe]++;
      return true;
    }
  return false;
}

void
CraftingManager::startRecipe (RecipeID id)
{
  recipes[id].start ();
}

void
CraftingManager::cancelRecipe (RecipeID id)
{
  recipes[id].cancel ();
}

unsigned
CraftingManager::getRemainingTicks (RecipeID id) const
{
  return recipes.at (id).getRemainingTicks ();
}

std::vector<std::pair<RessourceType, double> >
CraftingManager::getRecipe (RecipeID id)
{
  return recipes[id].getRecipe ();
}

bool
CraftingManager::tick ()
{
  bool ret = false;
  for (auto &[id, recipe] : recipes)
    {
      if (recipe.tick ())
        ret = true;
    }
  return ret;
}

std::vector<std::pair<RessourceType, double> >
CraftingManager::getCraftResults ()
{
  std::vector<std::pair<RessourceType, double> > result;
  for (const auto &[id, recipe] : recipes)
    {
      if (recipes.at (id).isDone ())
        {
          auto tmp = getCraftResult (id);
          result.insert (result.end (), tmp.begin (), tmp.end ());
        }
    }
  return result;
}

std::vector<std::pair<RessourceType, double> >
CraftingManager::getCraftResult (RecipeID id)
{
  return recipes.at (id).getBaseResult ();
}

unsigned
CraftingManager::getTotalRequiredTicks (RecipeID id) const
{
  return recipes.at (id).getTotalRequiredTicks ();
}

unsigned
CraftingManager::getAssignedNumOfJellies (RecipeID id) const
{
  return assignedNumbersOfJellies.at (id);
}

std::string
CraftingManager::getName (RecipeID id) const
{
  return recipes.at (id).getName ();
}