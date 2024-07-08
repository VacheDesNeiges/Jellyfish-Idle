#include "CraftingManager.hpp"

#include "CraftingRecipe.hpp"
#include "GameIDsTypes.hpp"
#include "RecipeID.hpp"

#include <utility>
#include <vector>

CraftingManager::CraftingManager ()
{
  recipes.reserve (CraftingRecipe::RecipeTypes.size ());
  for (const auto &c : CraftingRecipe::RecipeTypes)
    {
      recipes.try_emplace (c, c);
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

std::vector<std::pair<RecipeID, RecipeSaveData> >
CraftingManager::getData () const
{
  auto result = std::vector<std::pair<RecipeID, RecipeSaveData> > ();

  for (const auto craft : CraftingRecipe::RecipeTypes)
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