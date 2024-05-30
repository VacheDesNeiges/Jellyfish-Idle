#include "GardenManager.hpp"
#include "AquaCulture.hpp"

GardenManager::GardenManager ()
{
  cultures.reserve (AquaCulture::CultureTypes.size ());
  for (const auto &ac : AquaCulture::CultureTypes)
    {
      cultures.try_emplace (ac, ac);
    }
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