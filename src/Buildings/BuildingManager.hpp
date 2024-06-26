#pragma once
#include "Building.hpp"
#include "GameDataAccess.hpp"
#include "RessourceType.hpp"
#include "SaveAndLoadable.hpp"
#include <unordered_map>
#include <utility>
#include <vector>

class BuildingManager
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<BuildingType, unsigned> > >
{
public:
  BuildingManager ();
  ~BuildingManager () override = default;
  unsigned getCurrentQuantity (BuildingType);
  bool doesIncreasesMaxJellies (BuildingType);
  unsigned getIncreaseToMaxJfish (BuildingType);
  void buy (BuildingType);
  std::vector<std::pair<RessourceType, double> > nextBuyCost (BuildingType);

  std::vector<std::pair<RessourceType, double> > getProduction (BuildingType);
  std::vector<std::pair<RessourceType, double> > getConsumption (BuildingType);

  std::string getBuildingName (BuildingType) const;
  std::string getBuildingDescription (BuildingType) const;
  std::string getAdvancedDescription (BuildingType);

  std::unordered_map<RessourceType, double> getProductionRates () const;
  std::unordered_map<RessourceType, double> getConsumptionRates () const;

  std::vector<std::pair<BuildingType, unsigned> > getData () const override;
  void
  loadData (const std::vector<std::pair<BuildingType, unsigned> > &) override;

private:
  std::unordered_map<BuildingType, Building> buildings;
};