#include "JellyfishManager.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include "Jellyfish.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <span>
#include <string>
#include <utility>

JellyfishManager::JellyfishManager ()
{

  auto fstream = FilePaths::getFileStream (FilePaths::JobsPath);

  try
    {
      auto jobsJson = nlohmann::json::parse (fstream);

      const auto numJobs = jobsJson.at ("Jobs").size ();
      jobNumbers.reserve (numJobs);
      jobExp.reserve (numJobs);

      allJobs.reserve (numJobs);

      for (const auto &job : jobsJson.at ("Jobs"))
        {
          jobNumbers.try_emplace (JellyJob (job.at ("ID")), 0);
          jobExp.try_emplace (JellyJob (job.at ("ID")), 1, 0, 100);
          allJobs.push_back (JellyJob (job.at ("ID")));
          jobDescripions.try_emplace (JellyJob (job.at ("ID")),
                                      job.at ("Description"));
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing Jobs :\n" << e.what () << "\n";
      abort ();
    }

  for (const auto &job : allJobs)
    {
      jobNumbers.try_emplace (job, 0);
      jobExp.try_emplace (job, 1, 0, 100);
    }
}

unsigned int
JellyfishManager::getNum (JellyJob job)
{
  if (!numJobsUpToDate)
    updateNumJobs ();

  return jobNumbers[job];
};

void
JellyfishManager::zerosJobNumbersMap ()
{
  for (const auto &job : allJobs)
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
JellyfishManager::assign (JellyJob j)
{
  if (jobNumbers[JobsAlias::NONE] == 0)
    return false;
  auto it = std::ranges::find_if (jellies, [] (const auto &jelly) {
    return (jelly.getJob () == JobsAlias::NONE);
  });
  if (it == jellies.end ())
    return false;

  it->setJob (j);
  jobNumbers[JobsAlias::NONE] -= 1;
  jobNumbers[j] += 1;

  return true;
}

bool
JellyfishManager::unasign (JellyJob j)
{
  if (jobNumbers[j] == 0)
    return false;

  jobNumbers[j] -= 1;

  auto it = std::ranges::find_if (
      jellies, [j] (const auto &jelly) { return (jelly.getJob () == j); });

  if (it == jellies.end ())
    return false;

  it->setJob (JobsAlias::NONE);
  jobNumbers[JobsAlias::NONE] += 1;

  return true;
}

void
JellyfishManager::createJellyfish ()
{
  if (jellies.size () < maxNumJellies)
    {
      jellies.emplace_back ();
      jobNumbers[JobsAlias::NONE] += 1;
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
  using namespace RessourcesAlias;

  std::unordered_map<RessourceType, double> result;

  result[STONE] = (jobNumbers.at (JobsAlias::MINING) * 0.1)
                  * multipliersView ()->getProductionMultiplier (STONE);

  result[INSIGHT] = jobNumbers.at (JobsAlias::FOCUS) * 0.16;

  return result;
}

std::string
JellyfishManager::getJobDescription (JellyJob j) const
{

  if (jobDescripions.contains (j))
    return jobDescripions.at (j);

  return "Undefined Description";
}

JellyfishData
JellyfishManager::getData () const
{
  JellyfishData result;
  result.maxNumJellies = maxNumJellies;

  result.jobNumbers.reserve (jobNumbers.size ());
  for (const auto &[job, num] : jobNumbers)
    {
      result.jobNumbers.push_back ({ job, num });
    }
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

      for (const auto &[job, num] : data.jobNumbers)
        {
          for (unsigned i = 0; i < num; i++)
            {
              assign (job);
            }
        }
    }
}

bool
JellyfishManager::distributeJobExp ()
{
  bool hasLeveledUp = false;
  double progressGained;

  for (auto &[job, lvlStruct] : jobExp)
    {

      if (job == JobsAlias::ARTISAN)
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
JellyfishManager::getJobLevel (JellyJob j) const
{
  return jobExp.at (j).lvl;
}

double
JellyfishManager::getJobProgress (JellyJob j) const
{
  return jobExp.at (j).currentProgress;
}

double
JellyfishManager::getJobProgressNeeded (JellyJob j) const
{
  return jobExp.at (j).progressNeeded;
}

bool
JellyfishManager::canLure () const
{
  return LurePrice
             <= ressourcesView ()->getRessourceQuantity (RessourcesAlias::FOOD)
         && maxNumJellies > jellies.size ();
}

std::pair<RessourceType, double>
JellyfishManager::getLureCost () const
{
  return { RessourcesAlias::FOOD, LurePrice };
}

std::span<const JellyJob>
JellyfishManager::getAllJobsTypes () const
{
  return std::span (allJobs);
}