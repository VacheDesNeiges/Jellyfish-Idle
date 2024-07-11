#include "CraftingManager.hpp"

#include "CraftingRecipe.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <cstddef>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

CraftingManager::CraftingManager ()
{
  const auto fstream = FilePaths::getFileStream (FilePaths::RecipesPath);

  try
    {
      auto recipesJson = nlohmann::json::parse (fstream);

      const auto numRecipes = recipesJson.at ("Recipes").size ();
      recipes.reserve (numRecipes);
      recipeTypes.reserve (numRecipes);
      assignedJelliesToRecipes.reserve (numRecipes + 1);

      for (const auto &recipeData : recipesJson.at ("Recipes"))
        {
          recipes.try_emplace (RecipeID (recipeData.at ("ID")), recipeData);
          recipeTypes.push_back (RecipeID (recipeData.at ("ID")));
          assignedJelliesToRecipes[RecipeID (recipeData.at ("ID"))] = 0;
        }
      assignedJelliesToRecipes[RecipesAlias::NONE] = 0;
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing recipes :\n" << e.what () << "\n";
      abort ();
    }
}

bool
CraftingManager::assign (RecipeID id)
{
  if (assignedJelliesToRecipes[RecipesAlias::NONE] > 0)
    {
      assignedJelliesToRecipes[id]++;
      assignedJelliesToRecipes[RecipesAlias::NONE]--;
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
      assignedJelliesToRecipes[RecipesAlias::NONE]++;
      return true;
    }
  return false;
}

void
CraftingManager::startRecipe (RecipeID id)
{
  recipes.at (id).start ();
}

void
CraftingManager::cancelRecipe (RecipeID id)
{
  recipes.at (id).cancel ();
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
      = jelliesView ()->getNumJellies (JobsAlias::ARTISAN);
  if (assignedJelliesToCrafting == asssignedToJob)
    return;

  if (asssignedToJob > assignedJelliesToCrafting)
    {
      const auto dif = asssignedToJob - assignedJelliesToCrafting;

      assignedJelliesToRecipes[RecipesAlias::NONE] += dif;
      assignedJelliesToCrafting += dif;
    }
  else
    {
      const auto dif = assignedJelliesToCrafting - asssignedToJob;
      assignedJelliesToRecipes[RecipesAlias::NONE] -= dif;
      assignedJelliesToCrafting -= dif;
    }
}

bool
CraftingManager::canAfford (RecipeID id) const
{
  bool ret = true;
  for (const auto &[rType, quant] : getRecipe (id))
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

std::vector<std::pair<RecipeID, RecipeSaveData> >
CraftingManager::getData () const
{
  auto result = std::vector<std::pair<RecipeID, RecipeSaveData> > ();

  for (const auto craft : recipeTypes)
    {
      auto saveData = recipes.at (craft).getData ();
      saveData.numAssignedWorkers = getAssignedNumOfJellies (craft);
      result.emplace_back (craft, saveData);
    }
  return result;
}

void
CraftingManager::loadData (
    const std::vector<std::pair<RecipeID, RecipeSaveData> > &data)
{
  for (const auto &[id, recipeData] : data)
    {
      for (size_t i = 0; i < recipeData.numAssignedWorkers; i++)
        {
          assign (id);
        }
      recipes.at (id).loadData (recipeData);
    }
}

unsigned
CraftingManager::getAssignedNumOfJelliesOnOngoingCrafts () const
{
  unsigned result = 0;
  for (const auto &[id, recipe] : recipes)
    {
      if (recipe.isOngoing ())
        {
          result += getAssignedNumOfJellies (id);
        }
    }
  return result;
}

std::span<const RecipeID>
CraftingManager::getRecipeTypes () const
{
  return std::span (recipeTypes);
}