#include "Building.hpp"
#include "PlanktonField.hpp"
#include "Ressource.hpp"
#include "SandNest.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <math.h>
#include <memory>

void
Building::buy ()
{
  quantity++;
  update ();
  std::cout << "Bought new building, quantity : " << quantity << "\n";
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

std::string
Building::getBuildingName () const
{
  return name;
}

std::string
Building::getDescription ()
{
  std::string s;
  s = fmt::format ("{} ({})", name, quantity);

  return s;
}

std::string
Building::getAdvancedDescription ()
{
  std::string s = "price :";
  for (const auto &[ressource, price] : basePrice)
    {
      s += fmt::format ("\n{:.2f}", price * pow (priceMultiplier, quantity));
    }
  return s;
}

unsigned
Building::getIncreaseToMaxJfish () const
{
  return increaseToMaxJfish;
}