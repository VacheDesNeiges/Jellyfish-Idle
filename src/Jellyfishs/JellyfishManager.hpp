#pragma once
#include "GameDataAccess.hpp"
#include "GameSystems.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include <iostream>
#include <map>
#include <vector>

struct JellyfishData
{
  unsigned maxNumJellies;
  unsigned numJobNone;
  unsigned numJobExploreTheDepths;
  unsigned numJobGatheringSand;
  unsigned numJobMining;
  unsigned numJobFocusing;
  unsigned numJellies;
};

class GameDataView;

class JellyfishManager : public GameDataAcess
{
public:
  unsigned long getNumJellies () const;
  unsigned long getMaxNumJellies () const;
  void setBonusMaxJellies (unsigned);
  unsigned int getNum (JellyJobs);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);
  void createJellyfish ();
  std::vector<std::pair<RessourceType, double> > getProduction () const;
  std::map<RessourceType, double> getProductionRates () const;
  std::map<RessourceType, double> getConsumptionRates () const;
  std::string getJobDescription (JellyJobs) const;
  JellyfishData getData () const;
  void loadData (JellyfishData);

private:
  std::vector<Jellyfish> jellies;
  unsigned maxNumJellies = 1;

  bool numJobsUpToDate = false;
  unsigned numJobNone = 0;
  unsigned numJobExploreTheDepths = 0;
  unsigned numJobGatheringSand = 0;
  unsigned numJobMining = 0;
  unsigned numJobFocusing = 0;

  void updateNumJobs ();
};
