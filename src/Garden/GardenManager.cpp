#include "GardenManager.hpp"
#include "AquaCulture.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "MultiplierDataView.hpp"
#include "MultipliersIDs.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <span>
#include <string>
#include <utility>
#include <vector>

GardenManager::GardenManager ()
{
  const auto path = std::string (FilePaths::getPath ())
                    + std::string (FilePaths::CulturesPath);
  std::ifstream fstream (path);
  try
    {
      auto culturesJson = nlohmann::json::parse (fstream);

      const size_t numCultures = culturesJson.at ("Cultures").size ();
      cultures.reserve (numCultures);
      assignedFieldsToCultures.reserve (numCultures + 1);
      cultureTypes.reserve (numCultures);

      assignedFieldsToCultures[CulturesAlias::NONE] = 1;
      for (const auto &culture : culturesJson["Cultures"])
        {
          cultures.try_emplace (AquaCultureID (culture.at ("ID")), culture);
          assignedFieldsToCultures[AquaCultureID (culture.at ("ID"))] = 0;
          cultureTypes.push_back (AquaCultureID (culture.at ("ID")));
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing cultures :\n" << e.what () << "\n";
      abort ();
    }

  assignedFieldsToCultures[CulturesAlias::NONE] = 1;
}

void
GardenManager::startCulture (AquaCultureID id)
{
  cultures.at (id).start ();
}

void
GardenManager::cancelCulture (AquaCultureID id)
{
  cultures.at (id).cancel ();
}

bool
GardenManager::isOngoing (AquaCultureID id) const
{
  return cultures.at (id).isOngoing ();
}

std::vector<std::pair<AquaCultureID, CultureData> >
GardenManager::getData () const
{
  auto result = std::vector<std::pair<AquaCultureID, CultureData> > ();

  for (const auto culture : cultureTypes)
    {
      auto saveData = cultures.at (culture).getData ();
      saveData.fieldCount = getAssignedFieldsToCulture (culture);
      result.emplace_back (culture, saveData);
    }
  return result;
}

void
GardenManager::loadData (
    const std::vector<std::pair<AquaCultureID, CultureData> > &data)
{
  for (const auto &[culture, cultureData] : data)
    {
      for (size_t i = 0; i < cultureData.fieldCount; i++)
        {
          assign (culture);
        }
      cultures.at (culture).loadData (cultureData);
    }
}

std::vector<std::pair<RessourceType, double> >
GardenManager::getConsumption (AquaCultureID id) const
{
  auto vec = cultures.at (id).getBaseConsumption ();
  for (auto &[rType, val] : vec)
    {
      val *= assignedFieldsToCultures.at (id);
    }
  return vec;
}

std::vector<std::pair<RessourceType, double> >
GardenManager::getProduction (AquaCultureID id,
                              std::optional<unsigned> nFields) const
{
  auto vec = cultures.at (id).getBaseProduction ();

  using enum MultiplierID;
  for (auto &[rType, val] : vec)
    {
      val *= multipliersView ()->getMultiplier (FieldsProductivityMultiplier);
      val *= (nFields.value_or (assignedFieldsToCultures.at (id)));
    }

  return vec;
}

bool
GardenManager::canAffordTick (AquaCultureID id) const
{
  bool ret = true;
  const auto cost = getConsumption (id);
  for (const auto &[rType, quant] : cost)
    {
      if (ressourcesView ()->getRessourceQuantity (rType)
          < quant * assignedFieldsToCultures.at (id))
        {
          ret = false;
        }
    }
  return ret;
}

std::string
GardenManager::getName (AquaCultureID id) const
{
  return cultures.at (id).getName ();
}

unsigned
GardenManager::getTotalFields () const
{
  return maxFields;
}

unsigned
GardenManager::getAssignedFields () const
{
  return maxFields - assignedFieldsToCultures.at (CulturesAlias::NONE);
}

unsigned
GardenManager::getAssignedFieldsToCulture (AquaCultureID c) const
{
  return assignedFieldsToCultures.at (c);
}

bool
GardenManager::assign (AquaCultureID id)
{
  if (assignedFieldsToCultures.at (CulturesAlias::NONE) > 0)
    {
      assignedFieldsToCultures[id]++;
      assignedFieldsToCultures[CulturesAlias::NONE]--;
      return true;
    }
  return false;
}

bool
GardenManager::unnasign (AquaCultureID id)
{
  if (assignedFieldsToCultures.at (id) > 0)
    {
      assignedFieldsToCultures[id]--;
      assignedFieldsToCultures[CulturesAlias::NONE]++;
      return true;
    }
  return false;
}

std::span<const AquaCultureID>
GardenManager::getCultureTypes () const
{
  return std::span (cultureTypes);
}