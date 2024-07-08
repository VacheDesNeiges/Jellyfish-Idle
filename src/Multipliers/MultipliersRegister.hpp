#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "MultipliersIDs.hpp"

#include <array>
#include <unordered_map>

class MultipliersRegister : public GameDataAccess
{
public:
  MultipliersRegister ();

  double getMultiplier (MultiplierID) const;

  double getRessourceProdMultiplier (RessourceType) const;
  double getJobLvlMultiplier (JellyJob) const;
  double getBuildingMultiplier (BuildingType) const;

  void buildingBoughtUpdate (BuildingType);
  void addToMulitplier (MultiplierID, double);
  void recomputeMultipliers ();

private:
  std::unordered_map<MultiplierID, double> multipliers;

public: // constexpr arrays
  static constexpr std::array<std::pair<JellyJob, MultiplierID>, 1>
      jobLevelMultipliers = {
        std::pair{ JobsAlias::MINING, MultiplierID::MiningLevelMultiplier },
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