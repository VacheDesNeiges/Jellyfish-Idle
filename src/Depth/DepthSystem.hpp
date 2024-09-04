#pragma once

#include "GameDataAccess.hpp"
#include "SaveAndLoadable.hpp"
struct DepthData
{
    float currentProg;
    unsigned currentDepth;
};

class DepthSystem : public GameDataAccess, public SaveAndLoadable<DepthData>
{
  public:
    float getCurrentProgress() const;
    float getProgressNeededForNextIncrease() const;
    unsigned getCurrentDepth() const;
    unsigned getMaximumDepth() const;
    void ExploreDepth(unsigned nJellies);

    DepthData getData() const override;
    void loadData(const DepthData &data) override;

  private:
    float currentProgress = 0;
    float progressNeeded = 10;
    unsigned currentDepth = 5;
    unsigned maxDepth = 1000;
};
