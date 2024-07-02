#pragma once

#include "GameIDsTypes.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Building
{
public:
  Building () = default;
  explicit Building (const nlohmann::json &);

  ~Building () = default;

  void buy ();
  void update ();

  void setQuantity (unsigned);
  unsigned getCurrentQuantity () const;
  unsigned getIncreaseToMaxJfish () const;
  std::string getBuildingName () const;

  std::vector<std::pair<RessourceType, double> > getProdPerTick () const;
  std::vector<std::pair<RessourceType, double> > getConsumPerTick () const;
  std::vector<std::pair<RessourceType, double> > getNextBuyCost ();

  std::string getDescription () const;
  std::string getAdvancedDescription () const;

  const static std::vector<BuildingType> &getBuildingTypes ();
  const static std::vector<BuildingType> &getConversionBuildingTypes ();

private:
  friend class BuildingManager;
  static std::vector<BuildingType> buildingTypes;
  static std::vector<BuildingType> conversionBuildings;

  std::string name;
  std::string description;
  unsigned quantity = 0;
  unsigned increaseToMaxJfish = 0;
  double priceMultiplier = 1;
  std::vector<std::pair<RessourceType, double> > basePrice;
  std::unordered_map<RessourceType, const double> baseProductionPerTick;
  std::unordered_map<RessourceType, const double> baseConsumptionPerTick;
  std::unordered_map<RessourceType, const double> baseIncreasedStorage;

  std::vector<std::pair<RessourceType, double> > prodPerTick;
  std::vector<std::pair<RessourceType, double> > consumPerTick;
  std::vector<std::pair<RessourceType, double> > increasedStorage;
};
