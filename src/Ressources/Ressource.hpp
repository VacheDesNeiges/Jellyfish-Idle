#pragma once
#include <array>
#include <string>
#include <string_view>
#include <vector>

enum class RessourceType
{
  Food,
  Sand,
  Glass,
  Depth,
  Insight
};

// Contains Last as a workaround to allow iteration over the enum
// See CreateRessources for an exemple

class Ressource
{
public:
  Ressource () = default;
  explicit Ressource (RessourceType);
  ~Ressource () = default;
  void update (unsigned int ticks);
  void add (double n);
  double getCurrentQuantity () const;
  double getMaxQuantity () const;
  double getNetProduction () const;
  std::string_view getName () const;
  void resetValuesPerTick ();
  void addToConsumptionPerTick (double);
  void addToProdPerTick (double);
  void setQuantity (double);

  static constexpr std::array<RessourceType, 4> RessourceTypes
      = { RessourceType::Food, RessourceType::Sand, RessourceType::Glass,
          RessourceType::Insight };

  static constexpr std::array<RessourceType, 3> SpecialRessourcesTypes
      = { RessourceType::Depth };

private:
  bool specialRessource = false;
  std::string name;
  double quantity = 0;
  double max_quantity;
  // std::vector<float> production_multipliers;
  //? maybe use upgrades as boolean somewhere else ? Like in GameData

  double base_production; // per sec ?
  double prodPerTick;
  double consumptionPerTick;
};