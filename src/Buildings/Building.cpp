#include "Building.hpp"
#include "PlanktonField.hpp"
#include "Ressource.hpp"
#include "SandNest.hpp"
#include <cstddef>
#include <math.h>
#include <memory>

void
Building::buy ()
{
  quantity++;
  update ();
}

unsigned
Building::getCurrentQuantity () const
{
  return quantity;
}

std::unique_ptr<Building>
BuildingFactory::createBuildingInstance (BuildingType t)
{
  switch (t)
    {
    case BuildingType::PlanktonField:
      return std::make_unique<PlanktonField> ();
    case BuildingType::SandNest:
      return std::make_unique<SandNest> ();

    default:
      return nullptr;
    }
}

std::list<std::pair<RessourceType, double> >
Building::getNextBuyCost ()
{
  std::list<std::pair<RessourceType, double> > ret;
  for (auto &[ressource, cost] : basePrice)
    {
      ret.emplace_back (
          std::pair (ressource, cost * pow (priceMultiplier, quantity)));
    }
  return ret;
}
