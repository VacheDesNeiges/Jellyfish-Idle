#include "DepthDataView.hpp"

#include "DepthSystem.hpp"

DepthDataView::DepthDataView(const std::shared_ptr<DepthSystem> &dSystem)
    : depth(dSystem)
{
}

unsigned DepthDataView::getCurrentDepth() const
{
    return depth->getCurrentDepth();
}

unsigned DepthDataView::getMaximumDepth() const
{
    return depth->getMaximumDepth();
}

float DepthDataView::getCurrentProgress() const
{
    return depth->getCurrentProgress();
}

float DepthDataView::getProgressNeededForNextIncrease() const
{
    return depth->getProgressNeededForNextIncrease();
}
