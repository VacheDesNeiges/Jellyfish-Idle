#include "BuildingManager.hpp"

#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

BuildingManager::BuildingManager ()
{
  auto fstream = FilePaths::getFileStream (FilePaths::BuildingsPath);

  try
    {
      auto buildingsJson = nlohmann::json::parse (fstream);

      buildings.reserve (buildingsJson["Buildings"].size ());
      buildingTypes.reserve (buildingsJson["Buildings"].size ());

      for (const auto &building : buildingsJson["Buildings"])
        {
          buildings.try_emplace (BuildingType (building["BuildingID"]),
                                 building);

          buildingTypes.emplace_back (building["BuildingID"]);

          if (building.contains ("Conversion"))
            {
              conversionBuildingsTypes.emplace_back (building["BuildingID"]);
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
      prod *= multipliersView ()->getProductionMultiplier (t);
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
      if (std::ranges::find (conversionBuildingsTypes, bType)
          != conversionBuildingsTypes.end ())
        continue;

      for (const auto &[rType, productionRate] : b.getProdPerTick ())
        {
          result[rType]
              += (productionRate
                  * multipliersView ()->getProductionMultiplier (bType));
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
      if (std::ranges::find (conversionBuildingsTypes, bType)
          != conversionBuildingsTypes.end ())
        continue;

      for (const auto &[rType, consumptionRate] : b.getConsumPerTick ())
        {
          result[rType] += consumptionRate;
        }
    }
  return result;
}

bool
BuildingManager::doesIncreasesMaxJellies (BuildingType t) const
{
  return buildings.at (t).getIncreaseToMaxJfish () > 0;
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

std::span<const BuildingType>
BuildingManager::getBuildingTypes () const
{
  return std::span (buildingTypes);
}

std::span<const BuildingType>
BuildingManager::getConversionBuildingTypes () const
{
  return std::span (conversionBuildingsTypes);
}

bool
BuildingManager::doesIncreasesRessourcesMaxQuantities (BuildingType b) const
{
  return !buildings.at (b).getIncreasedStorage ().empty ();
}

std::span<const std::pair<RessourceType, double> >
BuildingManager::getIncreasedStorage (BuildingType b) const
{
  return buildings.at (b).getIncreasedStorage ();
}
