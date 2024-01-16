#pragma once
#include <utility>
#include <vector>

#include "RecipeID.hpp"
#include "Ressource.hpp"

class CraftingRecipe
{
public:
  CraftingRecipe () = default;
  explicit CraftingRecipe (RecipeID);
  ~CraftingRecipe () = default;

  unsigned getRemainingTicks () const;
  int getRecipelvl () const;
  void start ();
  void cancel ();

  std::vector<std::pair<RessourceType, double> > getRecipe () const;
  std::vector<std::pair<RessourceType, double> > getBaseResult () const;

  static constexpr std::array<RecipeID, 2> RecipeTypes
      = { RecipeID::StoneSlabRecipe, RecipeID::GlassPanelRecipe };

private:
  std::string recipeName;
  int recipeLvl = 0;

  unsigned baseTicksForCraft;
  unsigned remainingTicksToCraft;

  std::vector<std::pair<RessourceType, double> > recipe;
  std::vector<std::pair<RessourceType, double> > baseResult;
};