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
  unsigned getRemainingTicks (RecipeID) const;
  unsigned getTotalRequiredTicks (RecipeID) const;
  unsigned getAssignedNumOfJellies (RecipeID) const;
  std::string getName (RecipeID) const;

  bool tick ();
  std::vector<std::pair<RessourceType, double> > getRecipe (RecipeID);
  std::vector<std::pair<RessourceType, double> > getCraftResults ();
  std::vector<std::pair<RessourceType, double> > getCraftResult (RecipeID);

private:
  std::unordered_map<RecipeID, unsigned> assignedNumbersOfJellies;
  std::unordered_map<RecipeID, CraftingRecipe> recipes;
};