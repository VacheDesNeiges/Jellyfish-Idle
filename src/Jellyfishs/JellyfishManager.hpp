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
  unsigned numJobGatheringFood;
  unsigned numJobMining;
  unsigned numJobFocusing;
  unsigned numJellies;
};

class GameDataView;

class JellyfishManager : public GameDataAccess
{
public:
  JellyfishManager ();
  unsigned long getNumJellies () const;
  unsigned long getMaxNumJellies () const;
  void setBonusMaxJellies (unsigned);
  unsigned int getNum (JellyJobs);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);
  void createJellyfish ();
  std::map<RessourceType, double> getProductionRates () const;
  std::map<RessourceType, double> getConsumptionRates () const;
  std::string getJobDescription (JellyJobs) const;
  JellyfishData getData () const;
  void loadData (const JellyfishData &);

private:
  std::vector<Jellyfish> jellies;
  std::map<JellyJobs, unsigned> jobNumbers;
  unsigned maxNumJellies = 1;

  bool numJobsUpToDate = false;

  void updateNumJobs ();
  void zerosJobNumbersMap ();
};
