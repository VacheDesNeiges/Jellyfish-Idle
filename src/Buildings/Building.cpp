#include "Building.hpp"

#include "Ressource.hpp"

#include <fmt/core.h>
#include <math.h>
#include <utility>
#include <vector>

Building::Building (BuildingType bType)
{
  switch (bType)
    {

      using enum RessourceType;

    case BuildingType::PlanktonField:
      name = "Plankton Field";

      priceMultiplier = 1.15;
      basePrice.emplace_back (Food, 5);

      baseProductionPerTick.try_emplace (Food, 0.125);
      prodPerTick.emplace_back (Food, 0);
      break;

    case BuildingType::SandCurrentDucts:
      // Ducts that harness the currents,
      // allowing more nutrients to reach
      // the plankton field and increase its
      // production
      name = "Sand Current Ducts";
      priceMultiplier = 1.3;
      basePrice.emplace_back (Sand, 5);
      break;

    case BuildingType::DuneShelter:
      name = "Dune Shelter";
      increaseToMaxJfish = 1;

      priceMultiplier = 2;
      basePrice.emplace_back (Sand, 10);
      break;

    case BuildingType::Mines:
      name = "Mines";

      priceMultiplier = 1.2;
      basePrice.emplace_back (Stone, 25);
      break;

    case BuildingType::GlassTower:
      name = "Glass Tower";

      priceMultiplier = 1.3;
      basePrice.emplace_back (Glass, 50);
      break;

    case BuildingType::MarineStockRoom:
      name = "Marine Stockroom";
      priceMultiplier = 1.2;
      basePrice.emplace_back (StoneSlab, 12);
      basePrice.emplace_back (GlassPane, 10);
      break;
    }
}

void
Building::buy ()
{
  quantity++;
  updateProdPerTick ();
}

unsigned
Building::getCurrentQuantity () const
{
  return quantity;
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
Building::getDescription () // TODO : Move to UI ?
{
  std::string s;
  s = fmt::format ("{}, lvl {}", name, quantity);

  return s;
}

std::string
Building::getAdvancedDescription () const // TODO : Move to UI ?
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

void
Building::updateProdPerTick ()
{
  for (auto &[ressource, prod] : prodPerTick)
    {
      prod = baseProductionPerTick.at (ressource) * quantity;
    }
}

std::vector<std::pair<RessourceType, double> >
Building::getProdPerTick () const
{
  return prodPerTick;
}