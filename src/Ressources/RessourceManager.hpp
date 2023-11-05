#pragma once
#include "Ressource.hpp"
#include "map"
#include <utility>

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
  std::vector<std::pair<RessourceType, double> > getData () const;
  void loadData (const std::vector<std::pair<RessourceType, double> > &);

private:
  std::map<RessourceType, Ressource> ressources;
};