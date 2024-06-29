#include "Ressource.hpp"
#include "AchievementDataView.hpp"

#include <cfloat>
#include <string_view>
#include <vector>

std::vector<RessourceType> Ressource::ressourceTypes = {};
std::vector<RessourceType> Ressource::rareRessourceTypes = {};
std::vector<RessourceType> Ressource::craftableRessourceTypes = {};

Ressource::Ressource (const std::string &n, double max = DBL_MAX)
    : name (n), max_quantity (max)
{
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

const std::vector<RessourceType> &
Ressource::getRessourcesTypes ()
{
  return ressourceTypes;
}

const std::vector<RessourceType> &
Ressource::getRareRessourcesTypes ()
{
  return rareRessourceTypes;
}

const std::vector<RessourceType> &
Ressource::getCraftableRessourcesTypes ()
{
  return craftableRessourceTypes;
}