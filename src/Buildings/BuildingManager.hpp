#pragma once
#include "Building.hpp"
#include "GameDataAccess.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"
#include <memory>
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
  void updateRessources ();
  unsigned getCurrentQuantity (BuildingType);
  bool doesIncreasesMaxJellies (BuildingType);
  unsigned getIncreaseToMaxJfish (BuildingType);
  void buy (BuildingType);
  std::vector<std::pair<RessourceType, double> > nextBuyCost (BuildingType);

  std::list<std::pair<RessourceType, double> > getProduction (BuildingType);

  std::string getBuildingName (BuildingType);
  std::string getDescription (BuildingType);
  std::string getAdvancedDescription (BuildingType);

  std::unordered_map<RessourceType, double> getProductionRates () const;
  std::unordered_map<RessourceType, double> getConsumptionRates () const;

  std::vector<std::pair<BuildingType, unsigned> > getData () const override;
  void
  loadData (const std::vector<std::pair<BuildingType, unsigned> > &) override;

private:
  std::unordered_map<BuildingType, std::unique_ptr<Building> > buildings;
};