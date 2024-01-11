#include "MultiplierDataView.hpp"
#include "MultipliersIDs.hpp"
#include "MultipliersRegister.hpp"
#include <memory>

MultiplierDataView::MultiplierDataView (
    std::shared_ptr<MultipliersRegister> ptr)
    : multipliers (ptr)
{
}

double
MultiplierDataView::getMultiplier (MultiplierID id) const
{
  return multipliers->getMultiplier (id);
}

double
MultiplierDataView::getMultiplier (RessourceType rtype) const
{
  return multipliers->getMultiplierForRessourceProd (rtype);
}