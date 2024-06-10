#include "JellyfishDataView.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"

JellyFishDataView::JellyFishDataView (std::shared_ptr<JellyfishManager> j)
    : jellies (j)
{
}

unsigned int
JellyFishDataView::getNumJellies () const
{
  return jellies->getNumJellies ();
}

unsigned int
JellyFishDataView::getNumJellies (JellyJobs j) const
{
  return jellies->getNum (j);
}

unsigned int
JellyFishDataView::getMaxNumJellies () const
{
  return jellies->getMaxNumJellies ();
}

std::string
JellyFishDataView::getJobDescription (JellyJobs j) const
{
  return jellies->getJobDescription (j);
}

unsigned
JellyFishDataView::getJobLevel (JellyJobs j) const
{
  return jellies->getJobLevel (j);
}

double
JellyFishDataView::getCurrentProgress (JellyJobs j) const
{
  return jellies->getJobProgress (j);
}

double
JellyFishDataView::getProgressNeeded (JellyJobs j) const
{
  return jellies->getJobProgressNeeded (j);
}

bool
JellyFishDataView::canLure () const
{
  return jellies->canLure ();
}

std::pair<RessourceType, double>
JellyFishDataView::getLureCost () const
{
  return jellies->getLureCost ();
}