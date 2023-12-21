#pragma once
#include "JellyfishManager.hpp"
#include <memory>

class JellyFishDataView
{
public:
  explicit JellyFishDataView (std::shared_ptr<JellyfishManager>);

  unsigned long getNumJellies () const;
  long getNumJellies (JellyJobs) const;
  unsigned long getMaxNumJellies () const;
  std::string getJobDescription (JellyJobs) const;

private:
  std::shared_ptr<JellyfishManager> jellies;
};