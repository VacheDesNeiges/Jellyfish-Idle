#pragma once

#include "RessourceType.hpp"

#include <array>
#include <string>
#include <unordered_map>
#include <vector>
enum class BuildingType
{
  AquaticField,
  DuneShelter,
  Mines,
  GlassNests,
  GlassTower,
  MarineStockRoom,
  GlassBlowerAtelier,
  SubmergedLibrary,
  SolarLensFurnace,
};

class Building
{
public:
  Building () = default;
  explicit Building (BuildingType);

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

  static constexpr std::array<BuildingType, 9> BuildingTypes = {
    BuildingType::AquaticField,
    BuildingType::DuneShelter,
    BuildingType::Mines,
    BuildingType::GlassNests,
    BuildingType::GlassTower,
    BuildingType::MarineStockRoom,
    BuildingType::GlassBlowerAtelier,
    BuildingType::SubmergedLibrary,
    BuildingType::SolarLensFurnace,
  };

  static constexpr std::array<BuildingType, 1> convertionBuildings = {
    BuildingType::SolarLensFurnace,
  };

private:
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
