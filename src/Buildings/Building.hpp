#pragma once
#include "Ressource.hpp"
#include <string>
#include <unordered_map>
#include <vector>
enum class BuildingType
{
  PlanktonField,
  DuneShelter,
  Mines,
  GlassTower,
  MarineStockRoom,
};

class Building
{
public:
  Building () = default;
  explicit Building (BuildingType);

  ~Building () = default;

  void buy ();
  void updateProdPerTick ();

  void setQuantity (unsigned);
  unsigned getCurrentQuantity () const;
  unsigned getIncreaseToMaxJfish () const;
  std::string getBuildingName () const;

  std::vector<std::pair<RessourceType, double> > getProdPerTick () const;
  std::vector<std::pair<RessourceType, double> > getNextBuyCost ();

  std::string getDescription ();
  std::string getAdvancedDescription ();

  static constexpr std::array<BuildingType, 5> BuildingTypes = {
    BuildingType::PlanktonField,   BuildingType::DuneShelter,
    BuildingType::Mines,           BuildingType::GlassTower,
    BuildingType::MarineStockRoom,
  };

private:
  std::string name;
  unsigned quantity = 0;
  unsigned increaseToMaxJfish = 0;
  double priceMultiplier;
  std::vector<std::pair<RessourceType, double> > basePrice;
  std::unordered_map<RessourceType, const double> baseProductionPerTick;
  std::vector<std::pair<RessourceType, double> > prodPerTick;
};
