#include "MultiplierDataView.hpp"
#include "MultipliersRegister.hpp"
#include <memory>

MultiplierDataView::MultiplierDataView(
    const std::shared_ptr<MultipliersRegister> &ptr)
    : multipliers(ptr)
{
}

double MultiplierDataView::getMultiplier(MultiplierID id) const
{
    return multipliers->getMultiplier(id);
}

double MultiplierDataView::getProductionMultiplier(RessourceType rtype) const
{
    return multipliers->getRessourceProdMultiplier(rtype);
}

double MultiplierDataView::getProductionMultiplier(BuildingType bType) const
{
    return multipliers->getBuildingProdMultiplier(bType);
}

double MultiplierDataView::getAllFieldsMultiplier() const
{
    return multipliers->getAllFieldsMultiplier();
}
