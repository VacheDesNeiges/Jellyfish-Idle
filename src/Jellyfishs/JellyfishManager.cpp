#include "JellyfishManager.hpp"
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
    case GatherSeaShell:
      return numJobGatheringShells;
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
  numJobGatheringShells = 0;
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
        case GatherSeaShell:
          numJobGatheringShells++;
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
  auto it = std::find_if (
      jellies.begin (), jellies.end (),
      [] (const auto &jelly) { return (jelly.getJob () == JellyJobs::None); });
  if (it == jellies.end ())
    return false;

  it->setJob (j);
  numJobNone--;

  switch (j)
    {
    case JellyJobs::GatherFood:
      numJobGatheringFood++;
      break;
    case JellyJobs::GatherSeaShell:
      numJobGatheringShells++;
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

    case JellyJobs::GatherSeaShell:
      if (numJobGatheringShells == 0)
        return false;

      numJobGatheringShells--;
      break;

    case JellyJobs::Mining:
      if (numJobMining == 0)
        return false;

      numJobMining--;
      break;

    default:
      return false;
    }

  auto it = std::find_if (
      jellies.begin (), jellies.end (),
      [j] (const auto &jelly) { return (jelly.getJob () == j); });

  if (it == jellies.end ())
    return false;
  it->setJob (JellyJobs::None);
  numJobNone++;

  return true;
}