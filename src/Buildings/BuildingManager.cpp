#include "BuildingManager.hpp"

#include "Building.hpp"
#include "Ressource.hpp"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

BuildingManager::BuildingManager ()
{
  buildings.reserve (Building::BuildingTypes.size ());
  for (const auto &b : Building::BuildingTypes)
    {
      buildings[b] = Building (b);
    }
}

void
BuildingManager::buy (BuildingType t)
{
  buildings[t].buy ();
}

unsigned
BuildingManager::getCurrentQuantity (BuildingType t)
{
  return buildings[t].getCurrentQuantity ();
}

std::vector<std::pair<RessourceType, double> >
BuildingManager::getProduction (BuildingType t)
{
  auto result = buildings[t].getProdPerTick ();
  for (auto &[rType, prod] : result)
    {
      prod *= multipliersView ()->getBuildingMultiplier (t);
    }
  return result;
}

std::vector<std::pair<RessourceType, double> >
BuildingManager::getConsumption (BuildingType t)
{
  return buildings[t].getConsumPerTick ();
}

std::vector<std::pair<RessourceType, double> >
BuildingManager::nextBuyCost (BuildingType t)
{
  return buildings[t].getNextBuyCost ();
}

std::string
BuildingManager::getBuildingName (BuildingType t)
{
  return buildings[t].getBuildingName ();
}

std::string
BuildingManager::getAdvancedDescription (BuildingType t)
{
  return buildings[t].getAdvancedDescription ();
}

std::unordered_map<RessourceType, double>
BuildingManager::getProductionRates () const
{
  std::unordered_map<RessourceType, double> result;
  for (const auto &[bType, b] : buildings)
    {
      if (std::ranges::find (Building::convertionBuildings, bType)
          != Building::convertionBuildings.end ())
        continue;

      for (const auto &[rType, productionRate] : b.getProdPerTick ())
        {
          result[rType]
              += (productionRate
                  * multipliersView ()->getBuildingMultiplier (bType));
        }
    }
  return result;
}

std::unordered_map<RessourceType, double>
BuildingManager::getConsumptionRates () const
{
  std::unordered_map<RessourceType, double> result;
  for (const auto &[bType, b] : buildings)
    {
      if (std::ranges::find (Building::convertionBuildings, bType)
          != Building::convertionBuildings.end ())
        continue;

      for (const auto &[rType, consumptionRate] : b.getConsumPerTick ())
        {
          result[rType] += consumptionRate;
        }
    }
  return result;
}

bool
BuildingManager::doesIncreasesMaxJellies (BuildingType t)
{
  return buildings[t].getIncreaseToMaxJfish () > 0;
}

unsigned
BuildingManager::getIncreaseToMaxJfish (BuildingType t)
{
  return buildings[t].getIncreaseToMaxJfish ()
         * buildings[t].getCurrentQuantity ();
}

std::vector<std::pair<BuildingType, unsigned> >
BuildingManager::getData () const
{
  std::vector<std::pair<BuildingType, unsigned> > result;
  for (const auto &[type, building] : buildings)
    {
      result.emplace_back (type, building.getCurrentQuantity ());
    }

  return result;
}

void
BuildingManager::loadData (
    const std::vector<std::pair<BuildingType, unsigned> > &data)
{
  for (const auto &[type, quant] : data)
    {
      buildings[type].setQuantity (quant);
      buildings[type].update ();
    }
}
