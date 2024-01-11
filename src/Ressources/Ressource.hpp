#pragma once
#include "RessourceType.hpp"
#include <array>
#include <string>
#include <string_view>
#include <vector>

// Contains Last as a workaround to allow iteration over the enum
// See CreateRessources for an exemple

class Ressource
{
public:
  Ressource () = default;
  explicit Ressource (RessourceType);
  ~Ressource () = default;
  void add (double n);
  double getCurrentQuantity () const;
  double getMaxQuantity () const;
  double getNetProduction () const;
  double getProduction () const;
  double getConsumption () const;
  std::string_view getName () const;
  void resetValuesPerTick ();
  void addToConsumptionPerTick (double);
  void addToProdPerTick (double);
  void setQuantity (double);

  static constexpr std::array<RessourceType, 5> RessourceTypes
      = { RessourceType::Food, RessourceType::Sand, RessourceType::Stone,
          RessourceType::Glass, RessourceType::Insight };

  static constexpr std::array<RessourceType, 1> CraftableRessourceTypes
      = { RessourceType::StoneSlab };

private:
  bool specialRessource = false;
  std::string name;
  double quantity = 0;
  double max_quantity;

  double prodPerTick;
  double consumptionPerTick;
};