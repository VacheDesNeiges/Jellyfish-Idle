#pragma once
#include "GameIDsTypes.hpp"
#include <memory>

class MultipliersRegister;

class MultiplierDataView
{
  public:
    explicit MultiplierDataView(std::shared_ptr<MultipliersRegister>);

    double getMultiplier(MultiplierID) const;
    double getProductionMultiplier(RessourceType) const;
    double getProductionMultiplier(BuildingType) const;
    double getAllFieldsMultiplier() const;

  private:
    std::shared_ptr<const MultipliersRegister> multipliers;
};