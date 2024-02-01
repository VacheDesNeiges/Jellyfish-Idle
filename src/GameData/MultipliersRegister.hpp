#pragma once

#include "Building.hpp"
#include "GameDataAccess.hpp"
#include "Jellyfish.hpp"
#include "MultipliersIDs.hpp"
#include <array>
#include <unordered_map>
class MultipliersRegister : public GameDataAccess
{
public:
  MultipliersRegister ();

  double getMultiplier (MultiplierID) const;

  double getMultiplierForRessourceProd (RessourceType) const;

  void buildingBought (BuildingType);
  void addToMulitplier (MultiplierID, double);
  void recomputeMultipliers ();

  static constexpr std::array<std::pair<JellyJobs, MultiplierID>, 1>
      jobLevelMultipliers
      = { std::pair{ JellyJobs::Mining, MultiplierID::JobMiningProduction } };

  static constexpr std::array<std::pair<BuildingType, MultiplierID>, 1>
      buildingMultipliers = { std::pair{
          BuildingType::Mines, MultiplierID::StoneProdPerMineMultiplier } };

  static constexpr std::array<MultiplierID, 2> allMultipliers
      = { MultiplierID::StoneProdPerMineMultiplier,
          MultiplierID::JobMiningProduction };

private:
  std::unordered_map<MultiplierID, double> multipliers;
};