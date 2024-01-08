#include "Building.hpp"
#include "GlassTower.hpp"
#include "Mine.hpp"
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

    case BuildingType::Mines:
      return std::make_unique<Mine> ();

    case BuildingType::GlassTower:
      return std::make_unique<GlassTower> ();

    default:
      return nullptr;
    }
}

std::vector<std::pair<RessourceType, double> >
Building::getNextBuyCost ()
{
  std::vector<std::pair<RessourceType, double> > ret;
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
  s = fmt::format ("{}, lvl {}", name, quantity);

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

void
Building::setQuantity (unsigned quant)
{
  quantity = quant;
}