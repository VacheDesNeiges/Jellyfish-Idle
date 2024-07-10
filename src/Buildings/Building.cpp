#include "Building.hpp"

#include "GameIDsTypes.hpp"

#include <fmt/core.h>
#include <iostream>
#include <math.h>
#include <utility>
#include <vector>

Building::Building (const nlohmann::json &data)
{
  try
    {
      name = data.at ("Name");
      description = data.at ("Description");
      increaseToMaxJfish = data.at ("IncreaseToJfish");
      priceMultiplier = data.at ("PriceMultiplier");

      basePrice.reserve (data.at ("BasePrice").size ());
      for (const auto &price : data["BasePrice"])
        {
          basePrice.emplace_back (price.at ("RessourceID"),
                                  price.at ("Quantity"));
        }

      if (data.contains ("Conversion"))
        {
          for (const auto &cost : data["Conversion"].at ("Cost"))
            {
              baseConsumptionPerTick.try_emplace (
                  RessourceType (cost.at ("RessourceID")),
                  cost.at ("Quantity"));
            }
          for (const auto &prod : data["Conversion"].at ("Production"))
            {
              baseProductionPerTick.try_emplace (
                  RessourceType (prod.at ("RessourceID")),
                  prod.at ("Quantity"));
            }
        }

      if (data.contains ("StorageIncrease"))
        {
          for (const auto &storage : data["StorageIncrease"])
            {
              baseIncreasedStorage.try_emplace (
                  RessourceType (storage.at ("RessourceID")),
                  storage.at ("Quantity"));
            }
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