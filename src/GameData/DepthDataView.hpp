#pragma once
#include "DepthSystem.hpp"
#include <memory>

class DepthDataView
{
public:
  explicit DepthDataView (std::shared_ptr<DepthSystem>);

  float getCurrentProgress () const;
  float getProgressNeededForNextIncrease () const;
  unsigned getCurrentDepth () const;
  unsigned getMaximumDepth () const;

private:
  std::shared_ptr<DepthSystem> depth;
};