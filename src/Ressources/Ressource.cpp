#include "Ressource.hpp"

#include <cfloat>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <string_view>

Ressource::Ressource (const nlohmann::json &resData)
    : name (resData.at ("Name")),
      baseMaxQuantity (resData.value ("Max_Quantity", DBL_MAX)),
      maxQuantity (baseMaxQuantity)
{
}

void
Ressource::add (double n)
{
  if (n >= 0)
    {
      if (quantity + n <= maxQuantity)
        {
          quantity += n;
        }
      else
        {
          quantity = maxQuantity;
        }
    }
  else
    {
      if (quantity + n >= 0)
        {
          quantity += n;
        }
      else
        {
          quantity = 0;
        }
    }
}

double
Ressource::getCurrentQuantity () const
{
  return quantity;
}

double
Ressource::getMaxQuantity () const
{
  return maxQuantity;
}

std::string_view
Ressource::getName () const
{
  return name;
}

void
Ressource::resetValuesPerTick ()
{
  prodPerTick = 0;
  consumptionPerTick = 0;
}

void
Ressource::addToConsumptionPerTick (double n)
{
  consumptionPerTick += n;
}

void
Ressource::addToProdPerTick (double n)
{
  prodPerTick += n;
}

double
Ressource::getNetProduction () const
{
  return prodPerTick - consumptionPerTick;
}

void
Ressource::setQuantity (double quant)
{
  quantity = quant;
}

double
Ressource::getProduction () const
{
  return prodPerTick;
}

double
Ressource::getConsumption () const
{
  return consumptionPerTick;
}

void
Ressource::setBonusMaxQuantity (double n)
{
  maxQuantity = baseMaxQuantity + n;
}