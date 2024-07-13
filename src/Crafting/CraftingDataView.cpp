#include "CraftingDataView.hpp"

#include "CraftingManager.hpp"
#include "GameIDsTypes.hpp"

#include <memory>

CraftDataView::CraftDataView (std::shared_ptr<CraftingManager> c) : crafts (c)
{
}

unsigned
CraftDataView::getAssignedNumOfJellies (RecipeID id) const
{
  return crafts->getAssignedNumOfJellies (id);
}

unsigned
CraftDataView::getRemainingTicks (RecipeID id) const
{
  return crafts->getRemainingTicks (id);
}

unsigned
CraftDataView::getTotalRequiredTicks (RecipeID id) const
{
  return crafts->getTotalRequiredTicks (id);
}

std::string
CraftDataView::getName (RecipeID id) const
{
  return crafts->getName (id);
}

std::vector<std::pair<RessourceType, double> >
CraftDataView::getRecipe (RecipeID id) const
{
  return crafts->getRecipe (id);
}

std::vector<std::pair<RessourceType, double> >
CraftDataView::getCraftResults (RecipeID id) const
{
  return crafts->getCraftResult (id);
}

bool
CraftDataView::canAfford (RecipeID id) const
{
  return crafts->canAfford (id);
}

bool
CraftDataView::craftIsOngoing (RecipeID id) const
{
  return crafts->craftIsOngoing (id);
}

unsigned
CraftDataView::getAssignedNumOfJelliesOnOngoingCrafts () const
{
  return crafts->getAssignedNumOfJelliesOnOngoingCrafts ();
}

std::span<const RecipeID>
CraftDataView::getRecipeTypes () const
{
  return crafts->getRecipeTypes ();
}

bool
CraftDataView::isKeepCraftingEnabled (RecipeID id) const
{
  return crafts->isKeepCraftingEnabled (id);
}