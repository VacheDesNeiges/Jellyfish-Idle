#pragma once
#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "Jellyfish.hpp"
#include "SaveAndLoadable.hpp"
#include <span>
#include <unordered_map>
#include <utility>
#include <vector>

struct JellyfishData
{
    unsigned numJellies;
    unsigned maxNumJellies;
    std::vector<std::pair<JellyJob, unsigned>> jobNumbers;
};

struct JobLevel
{
    unsigned lvl = 0;
    double currentProgress = 0;
    double progressNeeded = 0;
};

class GameDataView;

class JellyfishManager : public GameDataAccess,
                         public SaveAndLoadable<JellyfishData>
{
  public:
    JellyfishManager();
    unsigned int getNum(JellyJob) const;
    unsigned int getNumJellies() const;
    unsigned int getMaxNumJellies() const;

    bool canLure() const;
    std::pair<RessourceType, double> getLureCost() const;

    void setBonusMaxJellies(unsigned);
    bool assign(JellyJob);
    bool unasign(JellyJob);
    void createJellyfish();

    std::unordered_map<RessourceType, double> getProductionRates() const;

    std::string getJobDescription(JellyJob) const;

    unsigned getJobLevel(JellyJob) const;
    double getJobProgress(JellyJob) const;
    double getJobProgressNeeded(JellyJob) const;
    bool distributeJobExp();

    std::span<const JellyJob> getAllJobsTypes() const;

    JellyfishData getData() const override;
    void loadData(const JellyfishData &) override;

  private:
    std::vector<JellyJob> allJobs;
    std::vector<Jellyfish> jellies;
    std::unordered_map<JellyJob, unsigned> jobNumbers;

    std::unordered_map<JellyJob, JobLevel>
        jobExp; // pair of current progress, progress neeeded
    std::unordered_map<JellyJob, std::string> jobDescripions;

    unsigned maxNumJellies = 1;
    static constexpr double LurePrice = 10;

    void updateNumJobs();
    void zerosJobNumbersMap();
};
