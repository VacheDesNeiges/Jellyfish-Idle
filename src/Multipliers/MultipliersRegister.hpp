#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "Multiplier.hpp"

#include <unordered_map>

class MultipliersRegister : public GameDataAccess
{
public:
  MultipliersRegister ();

  double getMultiplier (MultiplierID) const;
  double getRessourceProdMultiplier (RessourceType) const;
  double getJobLvlMultiplier (JellyJob) const;
  double getBuildingProdMultiplier (BuildingType) const;
  double getAllFieldsMultiplier () const;

private:
  std::unordered_map<MultiplierID, std::unique_ptr<Multiplier> > multipliers;

  struct
  {
    std::vector<MultiplierID> allFieldsProd;
    std::unordered_map<RessourceType, std::vector<MultiplierID> >
        ressourceProd;
    std::unordered_map<BuildingType, std::vector<MultiplierID> > buildingProd;
    std::unordered_map<JellyJob, std::vector<MultiplierID> > jobLvlProd;
  } multipliersCategories;
};