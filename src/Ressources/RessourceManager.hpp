#pragma once
#include "Ressource.hpp"
#include "map"

class RessourceManager
{
public:
  RessourceManager ();
  void init ();
  void updateRessources (int ticks);

  void gatherFood ();
  double getCurrentQuantity (RessourceType);
  double getMaxQuantity (RessourceType);
  std::string_view getName (RessourceType);

  void add (RessourceType, double);

private:
  std::map<RessourceType, Ressource> ressources;
};