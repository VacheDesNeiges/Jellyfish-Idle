#include "GardenDataView.hpp"
#include "AquaCulture.hpp"
#include "GardenManager.hpp"
#include <memory>

GardenDataView::GardenDataView (std::shared_ptr<GardenManager> g) : garden (g)
{
}

std::string
GardenDataView::getName (AquaCultureID id) const
{
  return garden->getName (id);
}

unsigned
GardenDataView::getAssignedFieldsToCulture (AquaCultureID id) const
{
  return garden->getAssignedFieldsToCulture (id);
}

bool
GardenDataView::isOngoing (AquaCultureID id) const
{
  return garden->isOngoing (id);
}