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

        case MultiplierID::FieldsProductivityMultiplier:
          {
            auto fieldsQuantity = buildingsView ()->getBuildingQuantity (
                BuildingType::AquaticField);

            multipliers[multi]
                += MultipliersConstants::FieldsProductivityMultiplier
                   * (fieldsQuantity - 1);
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

    case BuildingType::AquaticField:
      multipliers.at (MultiplierID::FieldsProductivityMultiplier)
          += MultipliersConstants::FieldsProductivityMultiplier;
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
    case RessourcesAlias::STONE:
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
    case BuildingType::AquaticField:
      return multipliers.at (MultiplierID::FieldsProductivityMultiplier);

    default:
      return 1;
    }
}