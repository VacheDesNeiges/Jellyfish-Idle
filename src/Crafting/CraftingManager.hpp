#pragma once
#include "CraftingRecipe.hpp"
#include "GameDataAccess.hpp"
#include "RecipeID.hpp"
#include <unordered_map>
#include <utility>

class CraftingManager : public GameDataAccess
{
public:
  CraftingManager ();
  ~CraftingManager () = default;

  bool assign (RecipeID);
  bool unasign (RecipeID);
  void startRecipe (RecipeID);
  void cancelRecipe (RecipeID);
  unsigned getRemainingTicks (RecipeID);

  bool tick ();
  std::vector<std::pair<RessourceType, double> > getRecipe (RecipeID);
  std::vector<std::pair<RessourceType, double> > getCraftResults ();

private:
  std::vector<std::pair<RessourceType, double> > getCraftResult (RecipeID);
  std::unordered_map<RecipeID, unsigned> assignedNumbersOfJellies;
  std::unordered_map<RecipeID, CraftingRecipe> recipes;
};