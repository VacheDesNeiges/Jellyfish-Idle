#include "BuildingDataView.hpp"

#include "Building.hpp"
#include "BuildingManager.hpp"
#include "RessourceManager.hpp"
#include <string>

BuildingDataView::BuildingDataView (std::shared_ptr<BuildingManager> b,
                                    std::shared_ptr<RessourceManager> r)
    : buildings (b), ressources (r)
{
}

bool
BuildingDataView::isBuyable (BuildingType t) const
{
  bool buyable = true;
  for (const auto &[ressource, price] : buildings->nextBuyCost (t))
    {
      if (price > ressources->getCurrentQuantity (ressource))
        buyable = false;
    }
  return buyable;
}

std::string
BuildingDataView::getBuildingName (BuildingType t) const
{
  return buildings->getBuildingName (t);
}

std::string
BuildingDataView::getBuildingDescription (BuildingType t) const
{
  return buildings->getBuildingDescription (t);
}

std::string
BuildingDataView::getAdvancedBuildingDescription (BuildingType t) const
{
  return buildings->getAdvancedDescription (t);
}

unsigned
BuildingDataView::getBuildingQuantity (BuildingType t) const
{
  return buildings->getCurrentQuantity (t);
}

std::vector<std::pair<RessourceType, double> >
BuildingDataView::getBuildingProduction (BuildingType t) const
{
  return buildings->getProduction (t);
}

std::vector<std::pair<RessourceType, double> >
BuildingDataView::getNextBuyCost (BuildingType b) const
{
  return buildings->nextBuyCost (b);
}