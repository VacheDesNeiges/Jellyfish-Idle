#pragma once
#include "AbilityDataView.hpp"
#include "GameIDsTypes.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <vector>

class Ressource
{

public:
  Ressource () = default;
  explicit Ressource (const nlohmann::json &);
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
  static const std::vector<RessourceType> &getRessourcesTypes ();
  static const std::vector<RessourceType> &getRareRessourcesTypes ();
  static const std::vector<RessourceType> &getCraftableRessourcesTypes ();

private:
  friend class RessourceManager;
  static std::vector<RessourceType> ressourceTypes;
  static std::vector<RessourceType> rareRessourceTypes;
  static std::vector<RessourceType> craftableRessourceTypes;

  std::string name;
  double quantity = 0;
  double max_quantity = -1;

  double prodPerTick = 0;
  double consumptionPerTick = 0;
};