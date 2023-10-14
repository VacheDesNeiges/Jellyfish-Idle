#include "BuildingManager.hpp"
#include "Building.hpp"
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