#include "Building.hpp"

#include "RessourceType.hpp"

#include <fmt/core.h>
#include <math.h>
#include <utility>
#include <vector>

Building::Building (BuildingType bType)
{
  switch (bType)
    {

      using namespace RessourcesAlias;

    case BuildingType::AquaticField:
      name = "Aquatic Field";
      description
          = "A delimited area used to cultivate useful flora and fauna. Each "
            "level in this building increase the productivity of the fields";
      priceMultiplier = 1.20;
      basePrice.emplace_back (SAND, 5);
      break;

    case BuildingType::DuneShelter:
      name = "Dune Shelter";
      description
          = "A dune shelter, each level provides room for housing one jellie.";
      increaseToMaxJfish = 1;

      priceMultiplier = 2;
      basePrice.emplace_back (SAND, 10);
      break;

    case BuildingType::Mines:
      name = "Mines";
      description
          = "Underwater mine, each level increases stone production by 10%";

      priceMultiplier = 1.2;
      basePrice.emplace_back (STONE, 25);
      break;

    case BuildingType::GlassNests:
      name = "Glass Nests";
      description = "A pretty glass nest, each level provides enough room to "
                    "house two jellies";
      increaseToMaxJfish = 2;
      priceMultiplier = 2.5;
      basePrice.emplace_back (GLASS, 30);
      break;

    case BuildingType::GlassTower:
      name = "Glass Tower";

      priceMultiplier = 1.3;
      basePrice.emplace_back (GLASS, 50);
      break;

    case BuildingType::MarineStockRoom:
      name = "Marine Stockroom";
      priceMultiplier = 1.2;
      basePrice.emplace_back (STONESLAB, 12);
      basePrice.emplace_back (GLASSPANE, 10);
      break;

    case BuildingType::SubmergedLibrary:
      name = "Submerged Library";
      priceMultiplier = 1.2;
      basePrice.emplace_back (STONE, 200);
      basePrice.emplace_back (KNOWLEDGETABLET, 5);
      break;

    case BuildingType::GlassBlowerAtelier:
      name = "Glassblower's Atelier";
      priceMultiplier = 1.5;
      basePrice.emplace_back (STONE, 100);
      basePrice.emplace_back (GLASS, 80);
      break;

    case BuildingType::SolarLensFurnace:
      name = "Solar Lens Furnace";
      priceMultiplier = 1.3;
      baseProductionPerTick.try_emplace (GLASS, 0.01);
      baseConsumptionPerTick.try_emplace (SAND, 0.15);
      basePrice.emplace_back (STONE, 200);
      basePrice.emplace_back (STONESLAB, 5);
      basePrice.emplace_back (GLASSPANE, 2);
    }
}

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
Building::getAdvancedDescription () const // TODO : Move to UI ?
{
  std::string s = "price :";
  for (const auto &[ressource, price] : basePrice)
    {
      s += fmt::format ("\n{:.3f}", price * pow (priceMultiplier, quantity));
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
Building::update ()
{
  for (auto &[ressource, prod] : prodPerTick)
    {
      prod = baseProductionPerTick.at (ressource) * quantity;
    }

  for (auto &[ressource, consum] : consumPerTick)
    {
      consum = baseConsumptionPerTick.at (ressource) * quantity;
    }

  for (auto &[ressource, bonusStorage] : increasedStorage)
    {
      bonusStorage = baseIncreasedStorage.at (ressource) * quantity;
    }
}

std::vector<std::pair<RessourceType, double> >
Building::getProdPerTick () const
{
  return prodPerTick;
}

std::vector<std::pair<RessourceType, double> >
Building::getConsumPerTick () const
{
  return consumPerTick;
}

std::string
Building::getDescription () const
{
  return description;
}