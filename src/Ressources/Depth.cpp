#include "Depth.hpp"
#include <math.h>

double
Depth::getCurrentDepth () const
{
  return currentDepth;
}

double
Depth::getMaximumDepth () const
{
  return maxDepth;
}

double
Depth::getCurrentProgress () const
{
  return currentProgress;
}

double
Depth::getProgressNeededForNextIncrease () const
{
  return progressNeeded;
}

void
Depth::ExploreDepth (unsigned nJellies)
{
  double progressGained = nJellies * 0.15;
  currentProgress += progressGained;
  while (currentProgress >= progressNeeded && currentDepth < maxDepth)
    {
      currentDepth += 5;
      currentProgress -= progressNeeded;
      progressNeeded = baseProgressNeeded * pow (1.15, currentDepth / 5);
    }
}