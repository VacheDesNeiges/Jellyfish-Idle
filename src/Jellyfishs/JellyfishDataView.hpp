#pragma once
#include "GameIDsTypes.hpp"

#include <memory>
#include <span>

class JellyfishManager;

class JellyFishDataView
{
public:
  explicit JellyFishDataView (std::shared_ptr<JellyfishManager>);

  bool canLure () const;
  std::pair<RessourceType, double> getLureCost () const;

  unsigned int getNumJellies () const;
  unsigned int getNumJellies (JellyJob) const;
  unsigned int getMaxNumJellies () const;

  std::string getJobDescription (JellyJob) const;

  unsigned getJobLevel (JellyJob) const;
  double getCurrentProgress (JellyJob) const;
  double getProgressNeeded (JellyJob) const;

  std::span<const JellyJob> getAllJobsTypes () const;

private:
  std::shared_ptr<const JellyfishManager> jellies;
};