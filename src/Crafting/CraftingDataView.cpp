#include "CraftingDataView.hpp"
#include "CraftingManager.hpp"
#include "RecipeID.hpp"
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