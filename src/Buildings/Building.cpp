#include "Building.hpp"

#include "GameIDsTypes.hpp"

#include <fmt/core.h>
#include <iostream>
#include <math.h>
#include <utility>
#include <vector>

std::vector<BuildingType> Building::buildingTypes = {};
std::vector<BuildingType> Building::conversionBuildings = {};

Building::Building (const nlohmann::json &data)
{
  try
    {
      name = data["Name"];
      description = data["Description"];
      increaseToMaxJfish = data["IncreaseToJfish"];
      priceMultiplier = data["PriceMultiplier"];

      basePrice.reserve (data["BasePrice"].size ());
      for (const auto &price : data["BasePrice"])
        {
          basePrice.emplace_back (price["RessourceID"], price["Quantity"]);
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing a building :\n" << e.what () << "\n";
      abort ();
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

const std::vector<BuildingType> &
Building::getBuildingTypes ()
{
  return buildingTypes;
}

const std::vector<BuildingType> &
Building::getConversionBuildingTypes ()
{
  return conversionBuildings;
}