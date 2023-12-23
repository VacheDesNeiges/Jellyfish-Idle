#pragma once
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "RessourceManager.hpp"
#include <memory>

class BuildingDataView
{
public:
  explicit BuildingDataView (std::shared_ptr<BuildingManager>,
                             std::shared_ptr<RessourceManager>);

  bool isBuyable (BuildingType) const;
  unsigned getBuildingQuantity (BuildingType) const;

  std::list<std::pair<RessourceType, double> >
      getBuildingProduction (BuildingType) const;

  std::string getBuildingName (BuildingType) const;
  std::string getBuildingDescription (BuildingType) const;
  std::string getAdvancedBuildingDescription (BuildingType) const;
  std::list<std::pair<RessourceType, double> >
      getNextBuyCost (BuildingType) const;

private:
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<RessourceManager> ressources;
};