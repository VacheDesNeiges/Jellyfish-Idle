#include "GameDataSynchronizer.hpp"
#include "Building.hpp"
#include "Ressource.hpp"
#include <src/Jellyfishs/Jellyfish.hpp>

void
GameDataSynchronizer::gameTick ()
{
  for (auto b = static_cast<int> (BuildingType::PlanktonField);
       b != static_cast<int> (BuildingType::Last); b++)
    {
      for (const auto &[ressource, quantity] :
           getBuildingProduction (static_cast<BuildingType> (b)))
        {
          ressources.add (ressource, quantity);
        }
    }
}

void
GameDataSynchronizer::gatherFood ()
{
  ressources.gatherFood ();
}

double
GameDataSynchronizer::getRessourceQuantity (RessourceType t)
{
  return ressources.getCurrentQuantity (t);
}

double
GameDataSynchronizer::getRessourceMaxQuantity (RessourceType t)
{
  return ressources.getMaxQuantity (t);
}

void
GameDataSynchronizer::buy (BuildingType t)
{
  buildings.buy (t);
}

unsigned
GameDataSynchronizer::getBuildingQuantity (BuildingType t)
{
  return buildings.getCurrentQuantity (t);
}

std::list<std::pair<RessourceType, double> >
GameDataSynchronizer::getBuildingProduction (BuildingType t)
{
  return buildings.getProduction (t);
}

long
GameDataSynchronizer::getNumJellies (JellyJobs j)
{
  return jellies.getNum (j);
}

bool
GameDataSynchronizer::assignJelly (JellyJobs j)
{
  return jellies.assign (j);
}

bool
GameDataSynchronizer::unassignJelly (JellyJobs j)
{
  return jellies.unasign (j);
}

std::string_view
GameDataSynchronizer::getRessourceName (RessourceType r)
{
  return ressources.getName (r);
}