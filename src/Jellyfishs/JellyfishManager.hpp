#pragma once
#include "Jellyfish.hpp"
#include <iostream>
#include <vector>

class JellyfishManager
{
public:
  unsigned long getNum () const;
  unsigned long getMaxNum () const;
  long getNum (JellyJobs);
  bool assign (JellyJobs);
  bool unasign (JellyJobs);
  void createJellyfish ();

private:
  std::vector<Jellyfish> jellies;

  void updateNumJobs ();
  bool numJobsUpToDate = false;
  unsigned numJobNone = 0;
  unsigned numJobMining = 0;
  unsigned numJobGatheringShells = 0;
  unsigned numJobGatheringFood = 0;
};