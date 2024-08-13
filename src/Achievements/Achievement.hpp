#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include <nlohmann/json_fwd.hpp>
#include <utility>
#include <vector>

class Achievement : public GameDataAccess
{
  public:
    Achievement() = default;
    explicit Achievement(const nlohmann::json &);

    bool isUnlocked() const;
    bool unlockConditionMet() const;
    void unlock();
    void setState(bool);

  private:
    bool unlocked = false;

    unsigned jfishNumCondition = 0;
    unsigned depthCondition = 0;
    bool anyRareRessource = false;
    bool AnyManufacturedRessource = false;
    std::vector<std::pair<RessourceType, int>> ressourceCondition;
    std::vector<std::pair<BuildingType, unsigned>> buildingsCondition;
    std::vector<std::pair<JellyJob, unsigned>> jobsCondition;
    std::vector<AchievementIDs> achievementsCondition;
    std::vector<UpgradeID> upgradeCondition;

    bool ressourcesConditionsMet() const;
    bool buildingConditionsMet() const;
    bool achievementConditionsMet() const;
    bool jobsConditionsMet() const;
    bool upgradeConditionMet() const;
};
