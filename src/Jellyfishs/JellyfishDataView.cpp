#include "JellyfishDataView.hpp"
#include "GameIDsTypes.hpp"
#include "JellyfishManager.hpp"

JellyFishDataView::JellyFishDataView(
    const std::shared_ptr<JellyfishManager> &jManager)
    : jellies(jManager)
{
}

unsigned int JellyFishDataView::getNumJellies() const
{
    return jellies->getNumJellies();
}

unsigned int JellyFishDataView::getNumJellies(JellyJob jJob) const
{
    return jellies->getNum(jJob);
}

unsigned int JellyFishDataView::getMaxNumJellies() const
{
    return jellies->getMaxNumJellies();
}

std::string JellyFishDataView::getJobDescription(JellyJob jJob) const
{
    return jellies->getJobDescription(jJob);
}

unsigned JellyFishDataView::getJobLevel(JellyJob jJob) const
{
    return jellies->getJobLevel(jJob);
}

double JellyFishDataView::getCurrentProgress(JellyJob jJob) const
{
    return jellies->getJobProgress(jJob);
}

double JellyFishDataView::getProgressNeeded(JellyJob jJob) const
{
    return jellies->getJobProgressNeeded(jJob);
}

bool JellyFishDataView::canLure() const
{
    return jellies->canLure();
}

std::pair<RessourceType, double> JellyFishDataView::getLureCost() const
{
    return jellies->getLureCost();
}

std::span<const JellyJob> JellyFishDataView::getAllJobsTypes() const
{
    return jellies->getAllJobsTypes();
}
