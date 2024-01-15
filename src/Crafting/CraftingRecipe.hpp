#pragma once
#include <utility>
#include <vector>

#include "Ressource.hpp"

class CraftingRecipe
{
public:
  CraftingRecipe ();
  ~CraftingRecipe () = default;

  unsigned getRemainingTime () const;
  int getRecipelvl () const;

  std::vector<std::pair<RessourceType, const double> > getRecipe () const;
  std::vector<std::pair<RessourceType, double> > getBaseResult () const;

private:
  const std::string s = "";
  unsigned ticksToCraft;
  int recipeLvl = 0;

  const unsigned baseTicksForCraft;
  std::vector<std::pair<RessourceType, const double> > recipe;
  std::vector<std::pair<RessourceType, double> > baseResult;
};