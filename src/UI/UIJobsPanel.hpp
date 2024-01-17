#pragma once
#include "Jellyfish.hpp"
#include "RecipeID.hpp"
#include "UIElement.hpp"

class UIJobsPanel : public UIElement
{
public:
  void render () const override;

private:
  void renderJobsControls (JellyJobs) const;
  void renderRecipes () const;
  void renderRecipe (RecipeID) const;
};