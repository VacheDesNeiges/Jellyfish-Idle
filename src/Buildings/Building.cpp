#include "Building.hpp"
#include "PlanktonField.hpp"
#include <cstddef>
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
    case BuildingType::Last:
      return nullptr;
    default:
      return nullptr;
    }
}