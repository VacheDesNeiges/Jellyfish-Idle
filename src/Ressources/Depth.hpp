#pragma once

class Depth
{
public:
  double getCurrentProgress () const;
  double getProgressNeededForNextIncrease () const;
  double getCurrentDepth () const;
  double getMaximumDepth () const;
  void ExploreDepth (unsigned nJellies);

private:
  double const baseProgressNeeded = 10;
  double currentProgress = 0;
  double progressNeeded = 10;
  double currentDepth = 5;
  double maxDepth = 1000;
};