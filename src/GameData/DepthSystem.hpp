#pragma once

class DepthSystem
{
public:
  float getCurrentProgress () const;
  float getProgressNeededForNextIncrease () const;
  unsigned getCurrentDepth () const;
  unsigned getMaximumDepth () const;
  void ExploreDepth (unsigned nJellies);

private:
  unsigned const baseProgressNeeded = 10;
  float currentProgress = 0;
  float progressNeeded = 10;
  unsigned currentDepth = 5;
  unsigned maxDepth = 1000;
};