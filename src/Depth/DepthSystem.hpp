#pragma once

#include "GameDataAccess.hpp"
#include "SaveAndLoadable.hpp"

struct DepthData
{
    float currentProg;
    unsigned currentDepth;
};

class DepthSystem final : public GameDataAccess,
                          public SaveAndLoadable<DepthData>
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
    static constexpr unsigned maxDepth = 1000;
    static constexpr float progressNeededInitValue = 10;
    static constexpr unsigned currentDepthInitValue = 5;

    float currentProgress = 0;
    float progressNeeded = progressNeededInitValue;
    unsigned currentDepth = currentDepthInitValue;
};
