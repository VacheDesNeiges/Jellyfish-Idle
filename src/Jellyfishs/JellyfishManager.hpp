#pragma once
#include "GameDataAccess.hpp"
#include "Jellyfish.hpp"
#include "MultipliersIDs.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"
#include <unordered_map>
#include <utility>
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
  unsigned int getNum (JellyJobs);
  unsigned int getNumJellies () const;
  unsigned int getMaxNumJellies () const;

  bool canLure () const;
  std::pair<RessourceType, double> getLureCost () const;

  void setBonusMaxJellies (unsigned);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);
  void createJellyfish ();

  std::unordered_map<RessourceType, double> getProductionRates () const;

  std::string getJobDescription (JellyJobs) const;

  unsigned getJobLevel (JellyJobs) const;
  double getJobProgress (JellyJobs) const;
  double getJobProgressNeeded (JellyJobs) const;
  bool distributeJobExp ();

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
  static constexpr double LurePrice = 10;

  void updateNumJobs ();
  void zerosJobNumbersMap ();
};
