#pragma once
#include "GameDataAccess.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"
#include "unordered_map"
#include <utility>
#include <vector>

class RessourceManager
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<RessourceType, double> > >
{
public:
  RessourceManager ();
  void init ();

  void gatherSand ();
  double getCurrentQuantity (RessourceType);
  double getMaxQuantity (RessourceType);
  double getNetProduction (RessourceType);
  double getProduction (RessourceType);
  double getConsumption (RessourceType);
  std::string_view getName (RessourceType);

  void zerosValuePerTick ();

  void add (RessourceType, double);
  void addToProdPerTick (RessourceType, double);

  void consume (const std::unordered_map<RessourceType, double> &);
  void produce (const std::unordered_map<RessourceType, double> &);
  void tryConvert (const std::vector<std::pair<RessourceType, double> > &,
                   const std::vector<std::pair<RessourceType, double> > &);

  std::vector<std::pair<RessourceType, double> > getData () const override;
  void
  loadData (const std::vector<std::pair<RessourceType, double> > &) override;

private:
  std::unordered_map<RessourceType, Ressource> ressources;
};