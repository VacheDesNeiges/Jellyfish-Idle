#pragma once

#include "GameDataAccess.hpp"
#include "MultipliersIDs.hpp"
#include <array>
#include <unordered_map>
class MultipliersRegister : public GameDataAccess
{
public:
  MultipliersRegister ();

  double getMultiplier (MultiplierID) const;
  void addToMultplier (MultiplierID, double);
  void recomputeMultipliers ();

  static constexpr std::array<MultiplierID, 1> allMultipliers
      = { MultiplierID::MiningProdPerMineMultiplier };

private:
  std::unordered_map<MultiplierID, double> multipliers;
};