#pragma once
#include "Building.hpp"
#include "GameDataAccess.hpp"
#include "Ressource.hpp"
#include <map>
#include <memory>
#include <utility>
#include <vector>

class BuildingManager : public GameDataAccess
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
  void loadData (const std::vector<std::pair<BuildingType, unsigned> > &);

private:
  std::map<BuildingType, std::unique_ptr<Building> > buildings;
};