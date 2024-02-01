#include "MultipliersRegister.hpp"
#include "Building.hpp"
#include "MultipliersConstants.hpp"
#include "MultipliersIDs.hpp"

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
                = getDataView ()->getBuildingsView ()->getBuildingQuantity (
                    BuildingType::Mines);

            multipliers[multi]
                += MultipliersConstants::StoneProdPerMine * minesQuant;
          }
          break;

        default:
          continue;
        }
    }
}

void
MultipliersRegister::buildingBought (BuildingType t)
{
  switch (t)
    {

    case BuildingType::Mines:

      multipliers.at (MultiplierID::StoneProdPerMineMultiplier)
          += MultipliersConstants::StoneProdPerMine;
      break;

    default:
      return;
    }
}

double
MultipliersRegister::getMultiplierForRessourceProd (RessourceType rtype) const
{
  switch (rtype)
    {
    case RessourceType::Stone:
      return multipliers.at (MultiplierID::StoneProdPerMineMultiplier);

    default:
      return 1;
    }
}