#pragma once
#include <memory>
#include <utility>
#include <vector>

class CraftingManager;
enum class RecipeID;
enum class RessourceType;

class CraftDataView
{
public:
  explicit CraftDataView (std::shared_ptr<CraftingManager>);
  unsigned getRemainingTicks (RecipeID) const;
  unsigned getTotalRequiredTicks (RecipeID) const;
  unsigned getAssignedNumOfJellies (RecipeID) const;
  std::string getName (RecipeID) const;

  std::vector<std::pair<RessourceType, double> > getRecipe (RecipeID) const;
  std::vector<std::pair<RessourceType, double> >
      getCraftResults (RecipeID) const;

private:
  std::shared_ptr<CraftingManager> crafts;
};