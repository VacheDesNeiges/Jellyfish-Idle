#pragma once
#include "RecipeID.hpp"
#include "UIElement.hpp"

class UIJobsPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderJobsControls () const;
  void renderRecipes () const;
  void renderRecipe (RecipeID) const;
  void displayRecipeText (RecipeID) const;
};