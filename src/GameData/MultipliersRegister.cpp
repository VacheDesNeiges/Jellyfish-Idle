#include "MultipliersRegister.hpp"
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
MultipliersRegister::addToMultplier (MultiplierID id, double val)
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
        case MultiplierID::MiningProdPerMineMultiplier:
          break;

        default:
          continue;
        }
    }
}