#pragma once
#include "CraftingRecipe.hpp"
#include "GameDataAccess.hpp"
#include "RecipeID.hpp"
#include "SaveAndLoadable.hpp"

#include <unordered_map>
#include <utility>

class CraftingManager final
    : public GameDataAccess,
      public SaveAndLoadable<
          std::vector<std::pair<RecipeID, RecipeSaveData> > >
{
public:
  CraftingManager ();
  ~CraftingManager () override = default;

  bool assign (RecipeID);
  bool unasign (RecipeID);
  bool canAfford (RecipeID) const;
  bool craftIsOngoing (RecipeID) const;
  bool distributeCraftsExp ();
  void startRecipe (RecipeID);
  void cancelRecipe (RecipeID);
  unsigned getRemainingTicks (RecipeID) const;
  unsigned getTotalRequiredTicks (RecipeID) const;
  unsigned getAssignedNumOfJellies (RecipeID) const;
  void updateAssignments ();
  std::string getName (RecipeID) const;

  bool tick ();
  std::vector<std::pair<RessourceType, double> > getRecipe (RecipeID) const;
  std::vector<std::pair<RessourceType, double> > getCraftResults ();
  std::vector<std::pair<RessourceType, double> > getCraftResult (RecipeID);

  std::vector<std::pair<RecipeID, RecipeSaveData> > getData () const override;
  void loadData (
      const std::vector<std::pair<RecipeID, RecipeSaveData> > &) override;

private:
  unsigned assignedJelliesToCrafting = 0;
  std::unordered_map<RecipeID, unsigned> assignedJelliesToRecipes;
  std::unordered_map<RecipeID, CraftingRecipe> recipes;
};