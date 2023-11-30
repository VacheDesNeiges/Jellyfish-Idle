#pragma once

struct DepthData
{
  float currentProg;
  unsigned currentDepth;
};

class DepthSystem
{
public:
  float getCurrentProgress () const;
  float getProgressNeededForNextIncrease () const;
  unsigned getCurrentDepth () const;
  unsigned getMaximumDepth () const;
  void ExploreDepth (unsigned nJellies);

  DepthData getData () const;
  void loadData (DepthData);

private:
  unsigned const baseProgressNeeded = 10;
  float currentProgress = 0;
  float progressNeeded = 10;
  unsigned currentDepth = 5;
  unsigned maxDepth = 1000;
};