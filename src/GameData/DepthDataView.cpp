#include "DepthDataView.hpp"
#include "DepthSystem.hpp"

DepthDataView::DepthDataView (std::shared_ptr<DepthSystem> d) : depth (d) {}

unsigned
DepthDataView::getCurrentDepth () const
{
  return depth->getCurrentDepth ();
}

unsigned
DepthDataView::getMaximumDepth () const
{
  return depth->getMaximumDepth ();
}

float
DepthDataView::getCurrentProgress () const
{
  return depth->getCurrentProgress ();
}

float
DepthDataView::getProgressNeededForNextIncrease () const
{
  return depth->getProgressNeededForNextIncrease ();
}