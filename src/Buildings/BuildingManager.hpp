#pragma once
#include "Building.hpp"
#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
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

  unsigned getCurrentQuantity (BuildingType) const;

  bool doesIncreasesMaxJellies (BuildingType) const;
  unsigned getIncreaseToMaxJfish (BuildingType);

  bool doesIncreasesRessourcesMaxQuantities (BuildingType) const;
  std::span<const std::pair<RessourceType, double> >
      getIncreasedStorage (BuildingType) const;

  void buy (BuildingType);
  std::vector<std::pair<RessourceType, double> >
      nextBuyCost (BuildingType) const;

  std::vector<std::pair<RessourceType, double> >
      getProduction (BuildingType) const;
  std::vector<std::pair<RessourceType, double> >
      getConsumption (BuildingType) const;

  std::unordered_map<RessourceType, double> getProductionRates () const;
  std::unordered_map<RessourceType, double> getConsumptionRates () const;

  std::string getBuildingName (BuildingType) const;
  std::string getBuildingDescription (BuildingType) const;
  std::string getAdvancedDescription (BuildingType) const;

  std::vector<std::pair<BuildingType, unsigned> > getData () const override;
  void
  loadData (const std::vector<std::pair<BuildingType, unsigned> > &) override;

  std::span<const BuildingType> getBuildingTypes () const;
  std::span<const BuildingType> getConversionBuildingTypes () const;

private:
  std::unordered_map<BuildingType, Building> buildings;

  std::vector<BuildingType> buildingTypes;
  std::vector<BuildingType> conversionBuildingsTypes;
};