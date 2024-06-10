#include "JellyfishManager.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"

#include <algorithm>
#include <cmath>
#include <string>

JellyfishManager::JellyfishManager ()
{
  for (const auto &job : Jellyfish::JobsTypes)
    {
      jobNumbers.try_emplace (job, 0);
      jobExp.try_emplace (job, 1, 0, 100);
    }
}

unsigned int
JellyfishManager::getNum (JellyJobs job)
{
  if (!numJobsUpToDate)
    updateNumJobs ();

  return jobNumbers[job];
};

void
JellyfishManager::zerosJobNumbersMap ()
{
  for (const auto &job : Jellyfish::JobsTypes)
    {
      jobNumbers[job] = 0;
    }
}

void
JellyfishManager::updateNumJobs ()
{
  zerosJobNumbersMap ();
  for (const auto &jfish : jellies)
    {
      jobNumbers[jfish.getJob ()] += 1;
    }
  numJobsUpToDate = true;
}

bool
JellyfishManager::assign (JellyJobs j)
{
  if (jobNumbers[JellyJobs::None] == 0)
    return false;
  auto it = std::ranges::find_if (jellies, [] (const auto &jelly) {
    return (jelly.getJob () == JellyJobs::None);
  });
  if (it == jellies.end ())
    return false;

  it->setJob (j);
  jobNumbers[JellyJobs::None] -= 1;
  jobNumbers[j] += 1;

  return true;
}

bool
JellyfishManager::unasign (JellyJobs j)
{
  if (jobNumbers[j] == 0)
    return false;

  jobNumbers[j] -= 1;

  auto it = std::ranges::find_if (
      jellies, [j] (const auto &jelly) { return (jelly.getJob () == j); });

  if (it == jellies.end ())
    return false;

  it->setJob (JellyJobs::None);
  jobNumbers[JellyJobs::None] += 1;

  return true;
}

void
JellyfishManager::createJellyfish ()
{
  if (jellies.size () < maxNumJellies)
    {
      jellies.emplace_back ();
      jobNumbers[JellyJobs::None] += 1;
    }
}

unsigned int
JellyfishManager::getNumJellies () const
{
  return static_cast<unsigned int> (jellies.size ());
}

unsigned int
JellyfishManager::getMaxNumJellies () const
{
  return maxNumJellies;
}

void
JellyfishManager::setBonusMaxJellies (unsigned n)
{
  maxNumJellies = n + 1;
}

std::unordered_map<RessourceType, double>
JellyfishManager::getProductionRates () const
{
  using enum JellyJobs;
  using enum RessourceType;

  std::unordered_map<RessourceType, double> result;

  result[Food] = jobNumbers.at (GatherFood) * 3;
  result[Sand] = jobNumbers.at (GatherSand) * 0.04;

  result[Stone] = (jobNumbers.at (Mining) * 0.1)
                  * multipliersView ()->getMultiplier (Stone);

  result[Insight] = jobNumbers.at (FocusForInsight) * 0.16;

  return result;
}

std::string
JellyfishManager::getJobDescription (JellyJobs j) const
{
  using enum JellyJobs;
  switch (j)
    {
    case GatherFood:
      return "Gather some food";

    case GatherSand:
      return "Gather Sand";

    case Mining:
      return "Mining for stone";

    case ExploreTheDepths:
      return "Explore the Depths";

    case FocusForInsight:
      return "Focus for Insight";

    case Artisan:
      return "Crafting Things";

    default:
      return "Undefined Description";
    }
}

JellyfishData
JellyfishManager::getData () const
{
  JellyfishData result;
  result.maxNumJellies = maxNumJellies;

  using enum JellyJobs;
  result.numJobGatheringFood = jobNumbers.at (GatherFood);
  result.numJobGatheringSand = jobNumbers.at (GatherSand);
  result.numJobExploreTheDepths = jobNumbers.at (ExploreTheDepths);
  result.numJobFocusing = jobNumbers.at (FocusForInsight);
  result.numJobMining = jobNumbers.at (Mining);
  result.numJobCrafting = jobNumbers.at (Artisan);
  result.numJobNone = jobNumbers.at (None);

  result.numJellies = static_cast<unsigned> (jellies.size ());

  return result;
}

void
JellyfishManager::loadData (const JellyfishData &data)
{
  maxNumJellies = data.maxNumJellies;
  jellies.reserve (maxNumJellies);

  if (data.numJellies > 0)
    {
      for (unsigned i = 0; i < data.numJellies; i++)
        {
          createJellyfish ();
        }

      for (unsigned i = 0; i < data.numJobFocusing; i++)
        {
          assign (JellyJobs::FocusForInsight);
        }

      for (unsigned i = 0; i < data.numJobExploreTheDepths; i++)
        {
          assign (JellyJobs::ExploreTheDepths);
        }
      for (unsigned i = 0; i < data.numJobGatheringSand; i++)
        {
          assign (JellyJobs::GatherSand);
        }

      for (unsigned i = 0; i < data.numJobMining; i++)
        {
          assign (JellyJobs::Mining);
        }

      for (unsigned i = 0; i < data.numJobCrafting; i++)
        {
          assign (JellyJobs::Artisan);
        }
    }

  using enum JellyJobs;
  jobNumbers[None] = data.numJobNone;
  jobNumbers[GatherFood] = data.numJobGatheringFood;
  jobNumbers[Mining] = data.numJobMining;
  jobNumbers[ExploreTheDepths] = data.numJobExploreTheDepths;
  jobNumbers[GatherSand] = data.numJobGatheringSand;
  jobNumbers[FocusForInsight] = data.numJobFocusing;
  jobNumbers[Artisan] = data.numJobCrafting;
}

bool
JellyfishManager::distributeJobExp ()
{
  bool hasLeveledUp = false;
  double progressGained;

  for (auto &[job, lvlStruct] : jobExp)
    {

      if (job == JellyJobs::Artisan)
        {
          progressGained
              = 0.5 * craftView ()->getAssignedNumOfJelliesOnOngoingCrafts ();
        }
      else
        {
          progressGained = jobNumbers.at (job) * 0.5;
        }
      lvlStruct.currentProgress += progressGained;

      while (lvlStruct.currentProgress >= lvlStruct.progressNeeded)
        {
          hasLeveledUp = true;
          lvlStruct.lvl += 1;
          lvlStruct.currentProgress -= lvlStruct.progressNeeded;
          lvlStruct.progressNeeded
              = 10 * lvlStruct.lvl
                * (lvlStruct.lvl / std::log (lvlStruct.lvl));
        }
    }

  return hasLeveledUp;
}

unsigned
JellyfishManager::getJobLevel (JellyJobs j) const
{
  return jobExp.at (j).lvl;
}

double
JellyfishManager::getJobProgress (JellyJobs j) const
{
  return jobExp.at (j).currentProgress;
}

double
JellyfishManager::getJobProgressNeeded (JellyJobs j) const
{
  return jobExp.at (j).progressNeeded;
}