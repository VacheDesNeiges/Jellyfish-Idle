#pragma once
#include <memory>

class JellyfishManager;
enum class JellyJobs;

class JellyFishDataView
{
public:
  explicit JellyFishDataView (std::shared_ptr<JellyfishManager>);

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