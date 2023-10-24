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
  double getNetProduction (RessourceType);
  std::string_view getName (RessourceType);

  void zerosValuePerTick ();

  void add (RessourceType, double);
  void addToProdPerTick (RessourceType, double);

  void consume (const std::map<RessourceType, double> &);
  void produce (const std::map<RessourceType, double> &);

private:
  std::map<RessourceType, Ressource> ressources;
};