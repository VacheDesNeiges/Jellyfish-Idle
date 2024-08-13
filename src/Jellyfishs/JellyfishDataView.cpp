#include "JellyfishDataView.hpp"
#include "GameIDsTypes.hpp"
#include "JellyfishManager.hpp"

JellyFishDataView::JellyFishDataView(std::shared_ptr<JellyfishManager> j)
    : jellies(j)
{
}

unsigned int JellyFishDataView::getNumJellies() const
{
    return jellies->getNumJellies();
}

unsigned int JellyFishDataView::getNumJellies(JellyJob j) const
{
    return jellies->getNum(j);
}

unsigned int JellyFishDataView::getMaxNumJellies() const
{
    return jellies->getMaxNumJellies();
}

std::string JellyFishDataView::getJobDescription(JellyJob j) const
{
    return jellies->getJobDescription(j);
}

unsigned JellyFishDataView::getJobLevel(JellyJob j) const
{
    return jellies->getJobLevel(j);
}

double JellyFishDataView::getCurrentProgress(JellyJob j) const
{
    return jellies->getJobProgress(j);
}

double JellyFishDataView::getProgressNeeded(JellyJob j) const
{
    return jellies->getJobProgressNeeded(j);
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