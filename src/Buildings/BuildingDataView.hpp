#pragma once
#include "GameIDsTypes.hpp"

#include <memory>
#include <span>
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

  std::span<const std::pair<RessourceType, double> >
      getIncreasedStorage (BuildingType) const;

  std::string getBuildingName (BuildingType) const;
  std::string getBuildingDescription (BuildingType) const;
  std::string getAdvancedBuildingDescription (BuildingType) const;
  std::vector<std::pair<RessourceType, double> >
      getNextBuyCost (BuildingType) const;

  std::span<const BuildingType> getBuildingTypes () const;
  std::span<const BuildingType> getConversionBuildingTypes () const;

private:
  std::shared_ptr<const BuildingManager> buildings;
  std::shared_ptr<const RessourceManager> ressources;
};