#pragma once
#include "GameIDsTypes.hpp"

#include <memory>
#include <vector>

class BuildingManager;
class RessourceManager;

class BuildingDataView
{
public:
  explicit BuildingDataView (std::shared_ptr<BuildingManager>,
                             std::shared_ptr<RessourceManager>);

  bool isBuyable (BuildingType) const;
  unsigned getBuildingQuantity (BuildingType) const;

  std::vector<std::pair<RessourceType, double> >
      getBuildingProduction (BuildingType) const;

  std::string getBuildingName (BuildingType) const;
  std::string getBuildingDescription (BuildingType) const;
  std::string getAdvancedBuildingDescription (BuildingType) const;
  std::vector<std::pair<RessourceType, double> >
      getNextBuyCost (BuildingType) const;

private:
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<RessourceManager> ressources;
};