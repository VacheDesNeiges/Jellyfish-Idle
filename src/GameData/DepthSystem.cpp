#include "DepthSystem.hpp"
#include <cmath>
#include <math.h>

unsigned
DepthSystem::getCurrentDepth () const
{
  return currentDepth;
}

unsigned
DepthSystem::getMaximumDepth () const
{
  return maxDepth;
}

float
DepthSystem::getCurrentProgress () const
{
  return currentProgress;
}

float
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