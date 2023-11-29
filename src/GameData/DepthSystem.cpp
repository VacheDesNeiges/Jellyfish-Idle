#include "DepthSystem.hpp"
#include <cmath>
#include <math.h>

double
DepthSystem::getCurrentDepth () const
{
  return currentDepth;
}

double
DepthSystem::getMaximumDepth () const
{
  return maxDepth;
}

double
DepthSystem::getCurrentProgress () const
{
  return currentProgress;
}

double
DepthSystem::getProgressNeededForNextIncrease () const
{
  return progressNeeded;
}

void
DepthSystem::ExploreDepth (unsigned nJellies)
{
  if (currentDepth < maxDepth)
    {
      double progressGained = nJellies * 0.5;
      currentProgress += progressGained;
      while (currentProgress >= progressNeeded)
        {
          currentDepth += 1;
          currentProgress -= progressNeeded;
          progressNeeded = currentDepth * (currentDepth / log (currentDepth));
        }
    }
}