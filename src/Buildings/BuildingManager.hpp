#pragma once
#include "Building.hpp"
#include "Ressource.hpp"
#include "map"
#include <memory>

class BuildingManager
{
public:
  BuildingManager ();
  void updateRessources ();
  unsigned getCurrentQuantity (BuildingType);
  void buy (BuildingType);

  std::list<std::pair<RessourceType, double> > getProduction (BuildingType);

private:
  std::map<BuildingType, std::unique_ptr<Building> > buildings;
};