#pragma once
#include "Building.hpp"
#include <memory>

class MultipliersRegister;
enum class MultiplierID;

class MultiplierDataView
{
public:
  explicit MultiplierDataView (std::shared_ptr<MultipliersRegister>);

  double getMultiplier (MultiplierID) const;
  double getMultiplier (RessourceType) const;
  double getBuildingMultiplier (BuildingType) const;

private:
  std::shared_ptr<MultipliersRegister> multipliers;
};