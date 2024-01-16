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
  if (assignedNumbers[RecipeID::NoneRecipe] > 0)
    {
      assignedNumbers[id]++;
      return true;
    }
  return false;
}

bool
CraftingManager::unasign (RecipeID id)
{
  if (assignedNumbers[id] > 0)
    {
      assignedNumbers[id]--;
      assignedNumbers[RecipeID::NoneRecipe]++;
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
CraftingManager::getRemainingTicks (RecipeID id)
{
  return recipes[id].getRemainingTicks ();
}

std::vector<std::pair<RessourceType, double> >
CraftingManager::getRecipe (RecipeID id)
{
  return recipes[id].getRecipe ();
}