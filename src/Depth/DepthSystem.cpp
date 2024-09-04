#include "DepthSystem.hpp"
#include <cmath>

unsigned DepthSystem::getCurrentDepth() const
{
    return currentDepth;
}

unsigned DepthSystem::getMaximumDepth() const
{
    return maxDepth;
}

float DepthSystem::getCurrentProgress() const
{
    return currentProgress;
}

float DepthSystem::getProgressNeededForNextIncrease() const
{
    return progressNeeded;
}

void DepthSystem::ExploreDepth(unsigned nJellies)
{
    if (currentDepth < maxDepth)
    {
        double progressGained = nJellies * 0.5;
        currentProgress += static_cast<float>(progressGained);
        while (currentProgress >= progressNeeded)
        {
            currentDepth += 1;
            currentProgress -= progressNeeded;
            progressNeeded = static_cast<float>(
                currentDepth * (currentDepth / std::log(currentDepth)));
        }
    }
}

DepthData DepthSystem::getData() const
{
    return {currentProgress, currentDepth};
}

void DepthSystem::loadData(const DepthData &data)
{
    currentProgress = data.currentProg;
    currentDepth = data.currentDepth;
    progressNeeded =
        static_cast<float>(currentDepth * (currentDepth / log(currentDepth)));
}
