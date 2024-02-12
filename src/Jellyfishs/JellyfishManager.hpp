#pragma once
#include "GameDataAccess.hpp"
#include "Jellyfish.hpp"
#include "MultipliersIDs.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"
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
  unsigned numJobCrafting;
  unsigned numJellies;
};

struct JobLevel
{
  unsigned lvl = 0;
  double currentProgress;
  double progressNeeded;
};

class GameDataView;

class JellyfishManager : public GameDataAccess,
                         public SaveAndLoadable<JellyfishData>
{
public:
  JellyfishManager ();
  unsigned int getNumJellies () const;
  unsigned int getMaxNumJellies () const;
  void setBonusMaxJellies (unsigned);
  unsigned int getNum (JellyJobs);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);
  bool distributeJobExp ();
  void createJellyfish ();
  double getFoodRequiredPerJellyfishPerSec () const;
  std::unordered_map<RessourceType, double> getProductionRates () const;
  std::unordered_map<RessourceType, double> getConsumptionRates () const;
  std::string getJobDescription (JellyJobs) const;

  unsigned getJobLevel (JellyJobs) const;
  double getJobProgress (JellyJobs) const;
  double getJobProgressNeeded (JellyJobs) const;

  JellyfishData getData () const override;
  void loadData (const JellyfishData &) override;

private:
  std::vector<Jellyfish> jellies;
  std::unordered_map<JellyJobs, unsigned> jobNumbers;

  std::unordered_map<JellyJobs, JobLevel>
      jobExp; // pair of current progress, progress neeeded

  std::unordered_map<MultiplierID, double> multipliers;

  unsigned maxNumJellies = 1;
  bool numJobsUpToDate = false;

  void updateNumJobs ();
  void zerosJobNumbersMap ();
};
