#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "Jellyfish.hpp"
#include "MultipliersIDs.hpp"

#include <array>
#include <unordered_map>

class MultipliersRegister : public GameDataAccess
{
public:
  MultipliersRegister ();

  double getMultiplier (MultiplierID) const;

  double getRessourceProdMultiplier (RessourceType) const;
  double getJobLvlMultiplier (JellyJobs) const;
  double getBuildingMultiplier (BuildingType) const;

  void buildingBoughtUpdate (BuildingType);
  void addToMulitplier (MultiplierID, double);
  void recomputeMultipliers ();

private:
  std::unordered_map<MultiplierID, double> multipliers;

public: // constexpr arrays
  static constexpr std::array<std::pair<JellyJobs, MultiplierID>, 1>
      jobLevelMultipliers = {
        std::pair{ JellyJobs::Mining, MultiplierID::MiningLevelMultiplier },
      };

  static constexpr std::array<std::pair<BuildingType, MultiplierID>, 2>
      buildingMultipliers = {
        std::pair{ BuildingsAlias::MINES,
                   MultiplierID::StoneProdPerMineMultiplier },
        std::pair{ BuildingsAlias::AQUATICFIELD,
                   MultiplierID::FieldsProductivityMultiplier },
      };

  static constexpr std::array<MultiplierID, 3> allMultipliers = {
    MultiplierID::StoneProdPerMineMultiplier,
    MultiplierID::MiningLevelMultiplier,
    MultiplierID::FieldsProductivityMultiplier,
  };
};