#include "RessourceManager.hpp"
#include "Ressource.hpp"

RessourceManager::RessourceManager () { init (); }

void
RessourceManager::init ()
{
  ressources[RessourceType::Food] = Ressource (RessourceType::Food);
  ressources[RessourceType::SeaShells] = Ressource (RessourceType::SeaShells);
  ressources[RessourceType::Minerals] = Ressource (RessourceType::Minerals);
}

void
RessourceManager::gatherFood ()
{
  ressources[RessourceType::Food].add (1);
}

double
RessourceManager::getCurrentQuantity (RessourceType t)
{
  return ressources[t].getCurrentQuantity ();
}

double
RessourceManager::getMaxQuantity (RessourceType t)
{
  return ressources[t].getMaxQuantity ();
}

void
RessourceManager::add (RessourceType t, double n)
{
  ressources[t].add (n);
}

std::string_view
RessourceManager::getName (RessourceType r)
{
  return ressources[r].getName ();
}