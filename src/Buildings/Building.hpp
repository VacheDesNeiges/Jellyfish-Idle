#pragma once
#include "Ressource.hpp"
#include <list>
#include <memory>
#include <string>
#include <utility>

enum class BuildingType
{
  PlanktonField,
  SandNest,
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
  unsigned getIncreaseToMaxJfish () const;
  std::list<std::pair<RessourceType, double> > getNextBuyCost ();
  std::string getBuildingName () const;
  virtual std::string getDescription ();
  virtual std::string getAdvancedDescription ();
  void setQuantity (unsigned);

private:
  std::string name;
  unsigned quantity = 0;

  std::list<std::pair<RessourceType, double> > basePrice;
  double priceMultiplier;

  std::list<std::pair<RessourceType, double> > prodPerTick;
  unsigned increaseToMaxJfish = 0;

  // Building classes ----------------------
  friend class PlanktonField;
  friend class SandNest;
};

class BuildingFactory
{
public:
  static std::unique_ptr<Building> createBuildingInstance (BuildingType);
};
