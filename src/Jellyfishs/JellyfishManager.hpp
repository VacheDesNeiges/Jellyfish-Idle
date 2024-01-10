#pragma once
#include "GameDataAccess.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"
#include <iostream>
#include <unordered_map>
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

class JellyfishManager : public GameDataAccess,
                         public SaveAndLoadable<JellyfishData>
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
  double getFoodRequiredPerJellyfishPerSec () const;
  std::unordered_map<RessourceType, double> getProductionRates () const;
  std::unordered_map<RessourceType, double> getConsumptionRates () const;
  std::string getJobDescription (JellyJobs) const;
  JellyfishData getData () const override;
  void loadData (const JellyfishData &) override;

private:
  std::vector<Jellyfish> jellies;
  std::unordered_map<JellyJobs, unsigned> jobNumbers;
  unsigned maxNumJellies = 1;

  bool numJobsUpToDate = false;

  void updateNumJobs ();
  void zerosJobNumbersMap ();
};
