#pragma once
#include <memory>

class JellyfishManager;
using RessourceType = int;
enum class JellyJobs;

class JellyFishDataView
{
public:
  explicit JellyFishDataView (std::shared_ptr<JellyfishManager>);

  bool canLure () const;
  std::pair<RessourceType, double> getLureCost () const;

  unsigned int getNumJellies () const;
  unsigned int getNumJellies (JellyJobs) const;
  unsigned int getMaxNumJellies () const;

  std::string getJobDescription (JellyJobs) const;

  unsigned getJobLevel (JellyJobs) const;
  double getCurrentProgress (JellyJobs) const;
  double getProgressNeeded (JellyJobs) const;

private:
  std::shared_ptr<JellyfishManager> jellies;
};