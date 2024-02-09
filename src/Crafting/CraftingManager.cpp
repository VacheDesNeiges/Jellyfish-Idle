#include "CraftingManager.hpp"

#include "CraftingRecipe.hpp"
#include "Jellyfish.hpp"
#include "RecipeID.hpp"
#include "Ressource.hpp"

#include <iostream>
#include <utility>
#include <vector>

CraftingManager::CraftingManager ()
{
  recipes.reserve (CraftingRecipe::RecipeTypes.size ());
  for (const auto &c : CraftingRecipe::RecipeTypes)
    {
      recipes[c] = CraftingRecipe (c);
      assignedJelliesToRecipes[c] = 0;
    }
  assignedJelliesToRecipes[RecipeID::NoneRecipe] = 0;
}

bool
CraftingManager::assign (RecipeID id)
{
  if (assignedJelliesToRecipes[RecipeID::NoneRecipe] > 0)
    {
      assignedJelliesToRecipes[id]++;
      assignedJelliesToRecipes[RecipeID::NoneRecipe]--;
      return true;
    }
  return false;
}

bool
CraftingManager::unasign (RecipeID id)
{
  if (assignedJelliesToRecipes[id] > 0)
    {
      assignedJelliesToRecipes[id]--;
      assignedJelliesToRecipes[RecipeID::NoneRecipe]++;
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
CraftingManager::getRecipe (RecipeID id) const
{
  return recipes.at (id).getRecipe ();
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
          for (auto &[rType, quant] : tmp)
            {
              quant *= assignedJelliesToRecipes[id];
              std::cout << "quant =" << quant << "\n";
            }
          result.insert (result.end (), tmp.begin (), tmp.end ());
          recipes.at (id).reset ();
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
  return assignedJelliesToRecipes.at (id);
}

std::string
CraftingManager::getName (RecipeID id) const
{
  return recipes.at (id).getName ();
}

void
CraftingManager::updateAssignments ()
{
  const auto asssignedToJob
      = jelliesView ()->getNumJellies (JellyJobs::Artisan);
  if (assignedJelliesToCrafting == asssignedToJob)
    return;

  if (asssignedToJob > assignedJelliesToCrafting)
    {
      const auto dif = asssignedToJob - assignedJelliesToCrafting;

      assignedJelliesToRecipes[RecipeID::NoneRecipe] += dif;
      assignedJelliesToCrafting += dif;
    }
  else
    {
      const auto dif = assignedJelliesToCrafting - asssignedToJob;
      assignedJelliesToRecipes[RecipeID::NoneRecipe] -= dif;
      assignedJelliesToCrafting -= dif;
    }
}

bool
CraftingManager::canAfford (RecipeID id) const
{
  bool ret = true;
  const auto recipe = getRecipe (id);
  for (const auto &[rType, quant] : recipe)
    {
      if (ressourcesView ()->getRessourceQuantity (rType)
          < quant * assignedJelliesToRecipes.at (id))
        ret = false;
    }
  return ret;
}

bool
CraftingManager::craftIsOngoing (RecipeID id) const
{
  return recipes.at (id).isOngoing ();
}

bool
CraftingManager::distributeCraftsExp ()
{
  bool hasLeveledUp = false;
  for (auto &[id, recipe] : recipes)
    {
      if (recipe.applyExp ())
        hasLeveledUp = true;
    }
  return hasLeveledUp;
}