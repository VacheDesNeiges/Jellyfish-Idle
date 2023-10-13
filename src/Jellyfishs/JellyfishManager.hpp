#pragma once
#include "Jellyfish.hpp"
#include <iostream>
#include <vector>

class JellyfishManager
{
public:
  long getNum (JellyJobs);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);

  JellyfishManager ()
  {
    jellies.emplace_back ();
    jellies.emplace_back ();

    jellies.emplace_back ();
  };

private:
  std::vector<Jellyfish> jellies;

  void updateNumJobs ();
  bool numJobsUpToDate = false;
  unsigned numJobNone = 0;
  unsigned numJobMining = 0;
  unsigned numJobGatheringShells = 0;
  unsigned numJobGatheringFood = 0;
};