#include "GardenDataView.hpp"
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

std::vector<std::pair<RessourceType, double> >
GardenDataView::getFieldCost (AquaCultureID id) const
{
  return garden->getCost (id);
}

std::vector<std::pair<RessourceType, double> >
GardenDataView::getFieldResults (AquaCultureID id) const
{
  return garden->getResult (id);
}

bool
GardenDataView::canAfford (AquaCultureID id) const
{
  return garden->canAfford (id);
}

unsigned
GardenDataView::getRemainingTicks (AquaCultureID id) const
{
  return garden->getRemainingTicks (id);
}

unsigned
GardenDataView::getTotalRequiredTicks (AquaCultureID id) const
{
  return garden->getTotalRequiredTicks (id);
}