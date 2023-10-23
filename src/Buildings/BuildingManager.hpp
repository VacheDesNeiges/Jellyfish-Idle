#pragma once
#include "Building.hpp"
#include "Ressource.hpp"
#include <map>
#include <memory>

class BuildingManager
{
public:
  BuildingManager ();
  void updateRessources ();
  unsigned getCurrentQuantity (BuildingType);
  void buy (BuildingType);
  std::list<std::pair<RessourceType, double> > nextBuyCost (BuildingType);

  std::list<std::pair<RessourceType, double> > getProduction (BuildingType);

  std::string getDescription (BuildingType);

  std::map<RessourceType, double> getProductionRates () const;
  std::map<RessourceType, double> getConsumptionRates () const;

private:
  std::map<BuildingType, std::unique_ptr<Building> > buildings;
};