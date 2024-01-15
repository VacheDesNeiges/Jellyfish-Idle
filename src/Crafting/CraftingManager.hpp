#pragma once
#include "CraftingRecipe.hpp"
#include "GameDataAccess.hpp"
#include "RecipeID.hpp"
#include <unordered_map>

class CraftingManager : public GameDataAccess
{
public:
  CraftingManager ();

  bool assign (RecipeID);
  bool unasign (RecipeID);
  bool startRecipe (RecipeID);
  void cancelRecipe (RecipeID);

  std::vector<std::pair<RessourceType, double> > getRecipeResult (RecipeID);

private:
  std::unordered_map<RecipeID, unsigned> assignedNumbers;
  std::unordered_map<RecipeID, CraftingRecipe> recipes;
};