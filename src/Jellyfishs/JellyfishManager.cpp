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

JellyfishManager::JellyfishManager()
{

    auto fstream = FilePaths::getFileStream(FilePaths::JobsPath);

    try
    {
        auto jobsJson = nlohmann::json::parse(fstream);

        const auto numJobs = jobsJson.at("Jobs").size();
        jobNumbers.reserve(numJobs);
        jobExp.reserve(numJobs);

        allJobs.reserve(numJobs);

        for (const auto &job : jobsJson.at("Jobs"))
        {
            jobNumbers.try_emplace(JellyJob(job.at("ID")), 0);
            jobExp.try_emplace(JellyJob(job.at("ID")), 1, 0, 100);
            allJobs.emplace_back(job.at("ID"));
            jobDescripions.try_emplace(JellyJob(job.at("ID")),
                                       job.at("Description"));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing Jobs :\n" << e.what() << "\n";
        abort();
    }

    for (const auto &job : allJobs)
    {
        jobNumbers.try_emplace(job, 0);
        jobExp.try_emplace(job, 1, 0, 100);
    }
}

unsigned int JellyfishManager::getNum(JellyJob job) const
{
    return jobNumbers.at(job);
};

void JellyfishManager::zerosJobNumbersMap()
{
    for (const auto &job : allJobs)
    {
        jobNumbers[job] = 0;
    }
}

void JellyfishManager::updateNumJobs()
{
    zerosJobNumbersMap();
    for (const auto &jfish : jellies)
    {
        jobNumbers[jfish.getJob()] += 1;
    }
}

bool JellyfishManager::assign(JellyJob jJob)
{
    if (jobNumbers[JobsAlias::NONE] == 0)
        return false;
    auto it = std::ranges::find_if(jellies, [](const auto &jelly) {
        return (jelly.getJob() == JobsAlias::NONE);
    });
    if (it == jellies.end())
        return false;

    it->setJob(jJob);
    jobNumbers[JobsAlias::NONE] -= 1;
    jobNumbers[jJob] += 1;

    return true;
}

bool JellyfishManager::unasign(JellyJob jJob)
{
    if (jobNumbers[jJob] == 0)
        return false;

    jobNumbers[jJob] -= 1;

    auto it = std::ranges::find_if(jellies, [jJob](const auto &jelly) {
        return (jelly.getJob() == jJob);
    });

    if (it == jellies.end())
        return false;

    it->setJob(JobsAlias::NONE);
    jobNumbers[JobsAlias::NONE] += 1;

    return true;
}

void JellyfishManager::createJellyfish()
{
    if (jellies.size() < maxNumJellies)
    {
        jellies.emplace_back();
        jobNumbers[JobsAlias::NONE] += 1;
    }
}

unsigned int JellyfishManager::getNumJellies() const
{
    return static_cast<unsigned int>(jellies.size());
}

unsigned int JellyfishManager::getMaxNumJellies() const
{
    return maxNumJellies;
}

void JellyfishManager::setBonusMaxJellies(unsigned n)
{
    maxNumJellies = n + 1;
}

std::unordered_map<RessourceType, double> JellyfishManager::getProductionRates()
    const
{
    using namespace RessourcesAlias;

    std::unordered_map<RessourceType, double> result;

    result[STONE] = (jobNumbers.at(JobsAlias::MINING) * 0.1) *
                    multipliersView()->getProductionMultiplier(STONE);

    result[INSIGHT] = jobNumbers.at(JobsAlias::FOCUS) * 0.16;

    return result;
}

std::string JellyfishManager::getJobDescription(JellyJob jJob) const
{

    if (jobDescripions.contains(jJob))
        return jobDescripions.at(jJob);

    return "Undefined Description";
}

JellyfishData JellyfishManager::getData() const
{
    JellyfishData result;
    result.maxNumJellies = maxNumJellies;

    result.jobNumbers.reserve(jobNumbers.size());
    for (const auto &[job, num] : jobNumbers)
    {
        result.jobNumbers.emplace_back(job, num);
    }
    result.numJellies = static_cast<unsigned>(jellies.size());

    return result;
}

void JellyfishManager::loadData(const JellyfishData &data)
{
    maxNumJellies = data.maxNumJellies;
    jellies.reserve(maxNumJellies);

    if (data.numJellies > 0)
    {
        for (unsigned i = 0; i < data.numJellies; i++)
        {
            createJellyfish();
        }

        for (const auto &[job, num] : data.jobNumbers)
        {
            for (unsigned i = 0; i < num; i++)
            {
                assign(job);
            }
        }
    }
}

bool JellyfishManager::distributeJobExp()
{
    bool hasLeveledUp = false;
    double progressGained{};

    for (auto &[job, lvlStruct] : jobExp)
    {

        if (job == JobsAlias::ARTISAN)
        {
            progressGained =
                0.5 * craftView()->getAssignedNumOfJelliesOnOngoingCrafts();
        }
        else
        {
            progressGained = jobNumbers.at(job) * 0.5;
        }
        lvlStruct.currentProgress += progressGained;

        while (lvlStruct.currentProgress >= lvlStruct.progressNeeded)
        {
            hasLeveledUp = true;
            lvlStruct.lvl += 1;
            lvlStruct.currentProgress -= lvlStruct.progressNeeded;
            lvlStruct.progressNeeded =
                10 * lvlStruct.lvl * (lvlStruct.lvl / std::log(lvlStruct.lvl));
        }
    }

    return hasLeveledUp;
}

unsigned JellyfishManager::getJobLevel(JellyJob jJob) const
{
    return jobExp.at(jJob).lvl;
}

double JellyfishManager::getJobProgress(JellyJob jJob) const
{
    return jobExp.at(jJob).currentProgress;
}

double JellyfishManager::getJobProgressNeeded(JellyJob jJob) const
{
    return jobExp.at(jJob).progressNeeded;
}

bool JellyfishManager::canLure() const
{
    return LurePrice <=
               ressourcesView()->getRessourceQuantity(RessourcesAlias::FOOD) &&
           maxNumJellies > jellies.size();
}

std::pair<RessourceType, double> JellyfishManager::getLureCost() const
{
    return {RessourcesAlias::FOOD, LurePrice};
}

std::span<const JellyJob> JellyfishManager::getAllJobsTypes() const
{
    return std::span(allJobs);
}
