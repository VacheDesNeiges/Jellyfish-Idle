#include "CraftingRecipe.hpp"
#include "RecipeID.hpp"
#include <cassert>

CraftingRecipe::CraftingRecipe (RecipeID id)
{
  switch (id)
    {
      using enum RessourceType;

    case RecipeID::StoneSlabRecipe:
      recipeName = "Stone Slab";
      baseTicksForCraft = 600;
      recipe.emplace_back (Stone, 200);
      baseResult.emplace_back (StoneSlab, 1);
      break;

    case RecipeID::GlassPanelRecipe:
      recipeName = "Glass Pane";
      baseTicksForCraft = 600;
      recipe.emplace_back (Glass, 100);
      baseResult.emplace_back (GlassPane, 1);
      break;

    default:
      assert (false);
    }
}