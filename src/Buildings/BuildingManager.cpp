#include "BuildingManager.hpp"
#include "Building.hpp"
#include "Ressource.hpp"
#include <iostream>
#include <string>
#include <utility>

BuildingManager::BuildingManager ()
{
  for (const auto &b : Building::BuildingTypes)
    {
      buildings[b] = BuildingFactory::createBuildingInstance (b);
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
BuildingManager::getBuildingName (BuildingType t)
{
  return buildings[t]->getBuildingName ();
}

std::string
BuildingManager::getDescription (BuildingType t)
{
  return buildings[t]->getDescription ();
}

std::string
BuildingManager::getAdvancedDescription (BuildingType t)
{
  return buildings[t]->getAdvancedDescription ();
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

bool
BuildingManager::doesIncreasesMaxJellies (BuildingType t)
{
  return buildings[t]->getIncreaseToMaxJfish () > 0;
}

unsigned
BuildingManager::getIncreaseToMaxJfish (BuildingType t)
{
  return buildings[t]->getIncreaseToMaxJfish ()
         * buildings[t]->getCurrentQuantity ();
}

std::vector<std::pair<BuildingType, unsigned> >
BuildingManager::getData () const
{
  std::vector<std::pair<BuildingType, unsigned> > result;
  for (const auto &[type, building] : buildings)
    {
      result.emplace_back (type, building->getCurrentQuantity ());
    }

  return result;
}

void
BuildingManager::loadData (
    const std::vector<std::pair<BuildingType, unsigned> > &data)
{
  for (const auto &[type, quant] : data)
    {
      buildings[type]->setQuantity (quant);
      buildings[type]->update ();
    }
}