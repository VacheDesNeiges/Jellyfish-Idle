#include "MultipliersRegister.hpp"

#include "Building.hpp"
#include "MultipliersConstants.hpp"
#include "MultipliersIDs.hpp"
#include <linux/limits.h>

MultipliersRegister::MultipliersRegister ()
{
  for (const auto &multi : allMultipliers)
    {
      multipliers[multi] = 1;
    }
}

double
MultipliersRegister::getMultiplier (MultiplierID id) const
{
  return multipliers.at (id);
}

void
MultipliersRegister::addToMulitplier (MultiplierID id, double val)
{
  multipliers[id] += val;
}

void
MultipliersRegister::recomputeMultipliers ()
{
  for (const auto &multi : allMultipliers)
    {
      multipliers.at (multi) = 1;

      switch (multi)
        {
        case MultiplierID::StoneProdPerMineMultiplier:
          {
            auto minesQuant
                = buildingsView ()->getBuildingQuantity (BuildingType::Mines);

            multipliers[multi]
                += MultipliersConstants::StoneProdPerMine * minesQuant;
          }
          break;

        case MultiplierID::FoodProdPerDuctMultiplier:
          {
            auto ductsQuant = buildingsView ()->getBuildingQuantity (
                BuildingType::SandCurrentDucts);

            multipliers[multi]
                += MultipliersConstants::FoodProdPerDuctMultiplier
                   * ductsQuant;
          }
          break;

        default:
          continue;
        }
    }
}

void
MultipliersRegister::buildingBoughtUpdate (BuildingType t)
{
  switch (t)
    {

    case BuildingType::Mines:

      multipliers.at (MultiplierID::StoneProdPerMineMultiplier)
          += MultipliersConstants::StoneProdPerMine;
      break;

    case BuildingType::SandCurrentDucts:
      multipliers.at (MultiplierID::FoodProdPerDuctMultiplier)
          += MultipliersConstants::FoodProdPerDuctMultiplier;
      break;

    default:
      return;
    }
}

double
MultipliersRegister::getRessourceProdMultiplier (RessourceType rtype) const
{
  switch (rtype)
    {
    case RessourceType::Stone:
      return multipliers.at (MultiplierID::StoneProdPerMineMultiplier);

    default:
      return 1;
    }
}

double
MultipliersRegister::getBuildingMultiplier (BuildingType bType) const
{
  switch (bType)
    {
    case BuildingType::PlanktonField:
      return multipliers.at (MultiplierID::FoodProdPerDuctMultiplier);

    default:
      return 1;
    }
}