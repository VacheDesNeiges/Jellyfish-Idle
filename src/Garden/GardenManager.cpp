#include "GardenManager.hpp"
#include "AquaCulture.hpp"
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

unsigned
GardenManager::getRemainingTicks (AquaCultureID id) const
{
  return cultures.at (id).getRemainingTicks ();
}

unsigned
GardenManager::getTotalRequiredTicks (AquaCultureID id) const
{
  return cultures.at (id).getTotalRequiredTicks ();
}

bool
GardenManager::isOngoing (AquaCultureID id) const
{
  return cultures.at (id).isOngoing ();
}

std::vector<int>
GardenManager::getData () const
{
  // TODO : implement save and load
  return { 1 };
}

void
GardenManager::loadData (const std::vector<int> &vec)
{
  // TODO implement
  return;
}

std::vector<std::pair<RessourceType, double> >
GardenManager::getCost (AquaCultureID id) const
{
  return cultures.at (id).getCost ();
}

std::vector<std::pair<RessourceType, double> >
GardenManager::getResult (AquaCultureID id) const
{
  return cultures.at (id).getResult ();
}

bool
GardenManager::canAfford (AquaCultureID id) const
{
  bool ret = true;
  const auto cost = getCost (id);
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

bool
GardenManager::tick ()
{
  bool ret = false;

  for (auto &[id, culture] : cultures)
    {
      if (culture.tick ())
        {
          ret = true;
        }
    }
  return ret;
}

std::vector<std::pair<RessourceType, double> >
GardenManager::getFieldsResults ()
{
  std::vector<std::pair<RessourceType, double> > result;
  for (const auto &[id, cost] : cultures)
    {
      if (cultures.at (id).isDone ())
        {
          auto tmp = getResult (id);
          result.insert (result.end (), tmp.begin (), tmp.end ());
          cultures.at (id).reset ();
        }
    }
  return result;
}