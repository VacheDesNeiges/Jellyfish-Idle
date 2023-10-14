#pragma once
#include "Ressource.hpp"
#include <list>
#include <memory>
#include <string>
#include <utility>

enum class BuildingType
{
  PlanktonField,
  Last
};

class Building
{
public:
  Building () = default;
  virtual ~Building () = default;

  void buy ();
  unsigned getCurrentQuantity () const;
  virtual void update () = 0;
  virtual std::list<std::pair<RessourceType, double> > getProdPerTick () = 0;
  std::list<std::pair<RessourceType, double> > getNextBuyCost ();
  virtual std::string getDescription () = 0;

private:
  std::string name;
  unsigned quantity = 0;

  std::list<std::pair<RessourceType, double> > basePrice;
  double priceMultiplier;

  std::list<std::pair<RessourceType, double> > prodPerTick;

  // Building classes ----------------------
  friend class PlanktonField;
};

class BuildingFactory
{
public:
  static std::unique_ptr<Building> createBuildingInstance (BuildingType);
};
