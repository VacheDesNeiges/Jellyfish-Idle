#include "JellyfishDataView.hpp"
#include "JellyfishManager.hpp"

JellyFishDataView::JellyFishDataView (std::shared_ptr<JellyfishManager> j)
    : jellies (j)
{
}

unsigned long
JellyFishDataView::getNumJellies () const
{
  return jellies->getNumJellies ();
}

long
JellyFishDataView::getNumJellies (JellyJobs j) const
{
  return jellies->getNum (j);
}

unsigned long
JellyFishDataView::getMaxNumJellies () const
{
  return jellies->getMaxNumJellies ();
}

std::string
JellyFishDataView::getJobDescription (JellyJobs j) const
{
  return jellies->getJobDescription (j);
}