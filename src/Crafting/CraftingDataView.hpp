#pragma once
#include "GameIDsTypes.hpp"

#include <memory>
#include <span>
#include <utility>
#include <vector>

class CraftingManager;

class CraftDataView
{
public:
  explicit CraftDataView (std::shared_ptr<CraftingManager>);
  unsigned getRemainingTicks (RecipeID) const;
  unsigned getTotalRequiredTicks (RecipeID) const;
  unsigned getAssignedNumOfJellies (RecipeID) const;
  unsigned getAssignedNumOfJelliesOnOngoingCrafts () const;
  bool canAfford (RecipeID) const;
  bool craftIsOngoing (RecipeID) const;
  std::string getName (RecipeID) const;

  std::vector<std::pair<RessourceType, double> > getRecipe (RecipeID) const;
  std::vector<std::pair<RessourceType, double> >
      getCraftResults (RecipeID) const;

  std::span<const RecipeID> getRecipeTypes () const;

private:
  std::shared_ptr<CraftingManager> crafts;
};