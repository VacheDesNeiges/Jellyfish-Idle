#include "Ressource.hpp"
#include <string_view>

Ressource::Ressource (RessourceType rType)
{

  switch (rType)
    {
    case RessourceType::Food:
      name = "Food";
      max_quantity = 2000;
      quantity = 0;
      break;

    case RessourceType::Sand:
      name = "Sand";
      max_quantity = 250;
      quantity = 0;
      break;

    case RessourceType::Stone:
      name = "Stone";
      max_quantity = 200;
      quantity = 0;
      break;

    case RessourceType::Insight:
      name = "Insight";
      max_quantity = 300;
      quantity = 0;
      break;

    case RessourceType::Glass:
      name = "Glass";
      max_quantity = 75;
      quantity = 0;
      break;

    case RessourceType::StoneSlab:
      name = "Stone Slab";
      max_quantity = 50;
      quantity = 0;

    default:
      break;
    }
}

void
Ressource::add (double n)
{
  if (n >= 0)
    {
      if (quantity + n <= max_quantity)
        {
          quantity += n;
        }
      else
        {
          quantity = max_quantity;
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
  return max_quantity;
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