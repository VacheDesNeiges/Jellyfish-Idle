#include "BuildingManager.hpp"
#include "Building.hpp"
#include "Ressource.hpp"
#include <iostream>

BuildingManager::BuildingManager ()
{
  for (auto b = static_cast<int> (BuildingType::PlanktonField);
       b != static_cast<int> (BuildingType::Last); b++)
    {
      buildings[static_cast<BuildingType> (b)]
          = BuildingFactory::createBuildingInstance (
              static_cast<BuildingType> (b));
    }
}

void
BuildingManager::buy (BuildingType t)
{
  buildings[t]->buy ();
}

unsigned
BuildingManager::getCurrentQuantity (BuildingType t)
{
  return buildings[t]->getCurrentQuantity ();
}

std::list<std::pair<RessourceType, double> >
BuildingManager::getProduction (BuildingType t)
{
  return buildings[t]->getProdPerTick ();
}

std::list<std::pair<RessourceType, double> >
BuildingManager::nextBuyCost (BuildingType t)
{
  return buildings[t]->getNextBuyCost ();
}

std::string
BuildingManager::getDescription (BuildingType t)
{
  return buildings[t]->getDescription ();
}

std::map<RessourceType, double>
BuildingManager::getProductionRates () const
{
  std::map<RessourceType, double> result;
  for (const auto &[_, b] : buildings)
    {
      for (const auto &[rType, productionRate] : b->getProdPerTick ())
        {
          result[rType] += productionRate;
        }
    }
  return result;
}

std::map<RessourceType, double>
BuildingManager::getConsumptionRates () const
{
  std::map<RessourceType, double> result;
  for (const auto &[_, b] : buildings)
    {
      for (const auto &[rType, consumptionRate] : b->getConsumPerTick ())
        {
          result[rType] += consumptionRate;
        }
    }
  return result;
}