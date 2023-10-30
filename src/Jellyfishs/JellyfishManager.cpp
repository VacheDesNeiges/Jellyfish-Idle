#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <src/Jellyfishs/Jellyfish.hpp>
#include <stdexcept>
#include <string>

long
JellyfishManager::getNum (JellyJobs job)
{
  if (!numJobsUpToDate)
    updateNumJobs ();

  switch (job)
    {
      using enum JellyJobs;
    case None:
      return numJobNone;
    case FocusForInsight:
      return numJobFocusing;
    case GatherSand:
      return numJobGatheringSand;
    case ExploreTheSea:
      return numJobExploreTheSea;
    case Last:
      throw std::invalid_argument (
          "Last should not be an allowed jellyfish job");
    }
};

void
JellyfishManager::updateNumJobs ()
{
  numJobNone = 0;
  numJobExploreTheSea = 0;
  numJobGatheringSand = 0;
  numJobFocusing = 0;
  for (const auto &jfish : jellies)
    {
      switch (jfish.getJob ())
        {
          using enum JellyJobs;
        case None:
          numJobNone++;
          break;
        case FocusForInsight:
          numJobFocusing++;
          break;
        case GatherSand:
          numJobGatheringSand++;
          break;
        case ExploreTheSea:
          numJobExploreTheSea++;
          break;
        default:
          break;
        }
    }
  numJobsUpToDate = true;
}

bool
JellyfishManager::assign (JellyJobs j)
{
  if (numJobNone == 0)
    return false;
  auto it = std::ranges::find_if (jellies, [] (const auto &jelly) {
    return (jelly.getJob () == JellyJobs::None);
  });
  if (it == jellies.end ())
    return false;

  it->setJob (j);
  numJobNone--;

  switch (j)
    {
    case JellyJobs::FocusForInsight:
      numJobFocusing++;
      break;
    case JellyJobs::GatherSand:
      numJobGatheringSand++;
      break;
    case JellyJobs::ExploreTheSea:
      numJobExploreTheSea++;
      break;
    default:
      return false;
    }
  return true;
}

bool
JellyfishManager::unasign (JellyJobs j)
{
  switch (j)
    {
    case JellyJobs::FocusForInsight:
      if (numJobFocusing == 0)
        return false;
      numJobFocusing--;

      break;

    case JellyJobs::GatherSand:
      if (numJobGatheringSand == 0)
        return false;
      numJobGatheringSand--;
      break;

    case JellyJobs::ExploreTheSea:
      if (numJobExploreTheSea == 0)
        return false;
      numJobExploreTheSea--;
      break;

    default:
      return false;
    }

  auto it = std::ranges::find_if (
      jellies, [j] (const auto &jelly) { return (jelly.getJob () == j); });

  if (it == jellies.end ())
    return false;
  it->setJob (JellyJobs::None);
  numJobNone++;

  return true;
}

void
JellyfishManager::createJellyfish ()
{
  jellies.emplace_back ();
  numJobNone++;
}

unsigned long
JellyfishManager::getNumJellies () const
{
  return jellies.size ();
}

unsigned long
JellyfishManager::getMaxNumJellies () const
{
  return maxNumJellies;
}

void
JellyfishManager::setBonusMaxJellies (unsigned n)
{
  maxNumJellies = n + 1;
}

std::vector<std::pair<RessourceType, double> >
JellyfishManager::getProduction () const
{
  std::vector<std::pair<RessourceType, double> > production;
  using enum RessourceType;
  production.emplace_back (Sand, numJobGatheringSand * 0.04);
  return production;
}

std::map<RessourceType, double>
JellyfishManager::getProductionRates () const
{
  std::map<RessourceType, double> result;
  using enum RessourceType;
  result[Sand] = numJobGatheringSand * 0.04;
  return result;
}

std::map<RessourceType, double>
JellyfishManager::getConsumptionRates () const
{
  std::map<RessourceType, double> result;
  using enum RessourceType;
  result[Food] = static_cast<double> (getNumJellies ()) * 0.5;
  return result;
}

std::string
JellyfishManager::getJobDescription (JellyJobs j) const
{
  using enum JellyJobs;
  switch (j)
    {
    case GatherSand:
      return "Gather Sand";

    case ExploreTheSea:
      return "Explore the sea";

    default:
      return "";
    }
}