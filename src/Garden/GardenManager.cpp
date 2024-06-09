#include "GardenManager.hpp"
#include "AquaCulture.hpp"
#include "AquaCultureID.hpp"
#include "MultiplierDataView.hpp"
#include "MultipliersIDs.hpp"
#include <utility>
#include <vector>

GardenManager::GardenManager ()
{
  cultures.reserve (AquaCulture::CultureTypes.size ());
  for (const auto &ac : AquaCulture::CultureTypes)
    {
      cultures.try_emplace (ac, ac);
      assignedFieldsToCultures[ac] = 0;
    }
  assignedFieldsToCultures[AquaCultureID::None] = 1;
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

  for (const auto culture : AquaCulture::CultureTypes)
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
GardenManager::getProduction (AquaCultureID id) const
{
  auto vec = cultures.at (id).getBaseProduction ();

  using enum MultiplierID;
  for (auto &[rType, val] : vec)
    {
      val *= multipliersView ()->getMultiplier (FieldsProductivityMultiplier);
      val *= assignedFieldsToCultures.at (id);
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
  return maxFields - assignedFieldsToCultures.at (AquaCultureID::None);
}

unsigned
GardenManager::getAssignedFieldsToCulture (AquaCultureID c) const
{
  return assignedFieldsToCultures.at (c);
}

bool
GardenManager::assign (AquaCultureID id)
{
  using enum AquaCultureID;
  if (assignedFieldsToCultures.at (None) > 0)
    {
      assignedFieldsToCultures[id]++;
      assignedFieldsToCultures[None]--;
      return true;
    }
  return false;
}

bool
GardenManager::unnasign (AquaCultureID id)
{
  using enum AquaCultureID;
  if (assignedFieldsToCultures.at (id) > 0)
    {
      assignedFieldsToCultures[id]--;
      assignedFieldsToCultures[None]++;
      return true;
    }
  return false;
}
