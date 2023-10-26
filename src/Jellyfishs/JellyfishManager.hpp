#pragma once
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include <iostream>
#include <map>
#include <vector>

class JellyfishManager
{
public:
  unsigned long getNumJellies () const;
  unsigned long getMaxNumJellies () const;
  void setBonusMaxJellies (unsigned);
  long getNum (JellyJobs);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);
  void createJellyfish ();
  std::vector<std::pair<RessourceType, double> > getProduction () const;
  std::map<RessourceType, double> getProductionRates () const;
  std::map<RessourceType, double> getConsumptionRates () const;

private:
  std::vector<Jellyfish> jellies;
  unsigned maxNumJellies = 1;

  bool numJobsUpToDate = false;
  unsigned numJobNone = 0;
  unsigned numJobExploreTheSea = 0;
  unsigned numJobGatheringSand = 0;
  unsigned numJobGatheringFood = 0;

  void updateNumJobs ();
};