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
  bool doesIncreasesMaxJellies (BuildingType);
  unsigned getIncreaseToMaxJfish (BuildingType);
  void buy (BuildingType);
  std::list<std::pair<RessourceType, double> > nextBuyCost (BuildingType);

  std::list<std::pair<RessourceType, double> > getProduction (BuildingType);

  std::string getBuildingName (BuildingType);
  std::string getDescription (BuildingType);
  std::string getAdvancedDescription (BuildingType);

  std::map<RessourceType, double> getProductionRates () const;
  std::map<RessourceType, double> getConsumptionRates () const;

  std::vector<std::pair<BuildingType, unsigned> > getData () const;
  void loadData ();

private:
  std::map<BuildingType, std::unique_ptr<Building> > buildings;
};