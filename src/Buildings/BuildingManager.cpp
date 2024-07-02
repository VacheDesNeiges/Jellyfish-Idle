#include "BuildingManager.hpp"

#include "Building.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

BuildingManager::BuildingManager ()
{
  const auto path = std::string (FilePaths::getPath ())
                    + std::string (FilePaths::BuildingsPath);
  std::ifstream fstream (path);
  try
    {
      auto buildingsJson = nlohmann::json::parse (fstream);

      buildings.reserve (buildingsJson["Buildings"].size ());
      Building::buildingTypes.reserve (buildingsJson["Buildings"].size ());

      for (const auto &building : buildingsJson["Buildings"])
        {
          buildings.try_emplace (BuildingType (building["BuildingID"]),
                                 building);

          Building::buildingTypes.emplace_back (building["BuildingID"]);

          if (building.contains ("Conversion"))
            {
              Building::conversionBuildings.emplace_back (
                  building["BuildingID"]);
            }
        }
    }

  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing buildings :\n" << e.what () << "\n";
      abort ();
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
BuildingManager::getBuildingName (BuildingType t) const
{
  return buildings.at (t).getBuildingName ();
}

std::string
BuildingManager::getBuildingDescription (BuildingType t) const
{
  return buildings.at (t).getDescription ();
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
      if (std::ranges::find (Building::getConversionBuildingTypes (), bType)
          != Building::getConversionBuildingTypes ().end ())
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
      if (std::ranges::find (Building::getConversionBuildingTypes (), bType)
          != Building::getConversionBuildingTypes ().end ())
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
