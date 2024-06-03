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
  return cultures.at (id).canAfford ();
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