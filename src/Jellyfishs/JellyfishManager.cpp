#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <src/Jellyfishs/Jellyfish.hpp>
#include <stdexcept>

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
    case GatherFood:
      return numJobGatheringFood;
    case GatherSand:
      return numJobGatheringSand;
    case Mining:
      return numJobMining;
    case Last:
      throw std::invalid_argument (
          "Last should not be an allowed jellyfish job");
    }
};

void
JellyfishManager::updateNumJobs ()
{
  numJobNone = 0;
  numJobMining = 0;
  numJobGatheringSand = 0;
  numJobGatheringFood = 0;
  for (const auto &jfish : jellies)
    {
      switch (jfish.getJob ())
        {
          using enum JellyJobs;
        case None:
          numJobNone++;
          break;
        case GatherFood:
          numJobGatheringFood++;
          break;
        case GatherSand:
          numJobGatheringSand++;
          break;
        case Mining:
          numJobMining++;
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
    case JellyJobs::GatherFood:
      numJobGatheringFood++;
      break;
    case JellyJobs::GatherSand:
      numJobGatheringSand++;
      break;
    case JellyJobs::Mining:
      numJobMining++;
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
    case JellyJobs::GatherFood:
      if (numJobGatheringFood == 0)
        return false;

      numJobGatheringFood--;

      break;

    case JellyJobs::GatherSand:
      if (numJobGatheringSand == 0)
        return false;

      numJobGatheringSand--;
      break;

    case JellyJobs::Mining:
      if (numJobMining == 0)
        return false;

      numJobMining--;
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
  return 1;
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
  result[Food] = static_cast<double> (getNumJellies ()) * 1;
  return result;
}