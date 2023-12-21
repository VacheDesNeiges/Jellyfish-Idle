#include "RessourceDataView.hpp"
#include "RessourceManager.hpp"

RessourceDataView::RessourceDataView (std::shared_ptr<RessourceManager> r)
    : ressources (r)
{
}

double
RessourceDataView::getRessourceProduction (RessourceType r) const
{
  return ressources->getProduction (r);
}

double
RessourceDataView::getRessourceConsumption (RessourceType r) const
{
  return ressources->getConsumption (r);
}

std::string_view
RessourceDataView::getRessourceName (RessourceType r) const
{
  return ressources->getName (r);
}

double
RessourceDataView::getRessourceQuantity (RessourceType t) const
{
  return ressources->getCurrentQuantity (t);
}

double
RessourceDataView::getRessourceMaxQuantity (RessourceType t) const
{
  return ressources->getMaxQuantity (t);
}