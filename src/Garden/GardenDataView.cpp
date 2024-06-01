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