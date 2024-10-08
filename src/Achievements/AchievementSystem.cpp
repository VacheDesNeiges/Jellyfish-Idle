#include "AchievementSystem.hpp"

#include "AchievementDataView.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

AchievementSystem::AchievementSystem()
{
    auto fstream = FilePaths::getFileStream(FilePaths::AchievementsPath);

    try
    {
        auto json = nlohmann::json::parse(fstream);

        achievements.reserve(json.at("Achievements").size());
        idMaps.allAchievementsIDs.reserve(json.at("Achievements").size());

        for (const auto &achiev : json.at("Achievements"))
        {
            achievements.try_emplace(AchievementIDs(achiev.at("ID")), achiev);
            insertIdInSearchMaps(achiev);
            if (achiev.contains("Notification"))
            {
                notifications.try_emplace(AchievementIDs(achiev.at("ID")),
                                          achiev.at("Notification"));
            }

            if (achiev.contains("DepthReward"))
            {
                parseDepthReward(achiev);
            }
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing achievements :\n" << e.what() << "\n";
        abort();
    }

    auto comparator = [](const auto &lhs, const auto &rhs) {
        return std::get<1>(lhs) > std::get<1>(rhs);
    };
    std::ranges::sort(depthRewards, comparator);
}

void AchievementSystem::parseDepthReward(const nlohmann::json &achiev)
{
    depthRewards.emplace_back(std::tuple{
        AchievementIDs(achiev.at("ID")), achiev.at("Condition")[0].at("Depth"),
        achiev.at("DepthReward").at("Name"),
        achiev.at("DepthReward").at("Description")});
}

void AchievementSystem::insertIdInSearchMaps(const nlohmann::json &achievement)
{
    idMaps.allAchievementsIDs.emplace_back(achievement.at("ID"));

    if (achievement.at("Type") == "Ressource")
        idMaps.ressources.emplace(achievement.at("RessourceID"),
                                  achievement.at("ID"));

    if (achievement.at("Type") == "Building")
        idMaps.buildings.emplace(achievement.at("BuildingID"),
                                 achievement.at("ID"));

    if (achievement.at("Type") == "JfishJob")
        idMaps.jobs.emplace(achievement.at("JobID"), achievement.at("ID"));

    if (achievement.at("Type") == "Garden")
        idMaps.cultures.emplace(achievement.at("CultureID"),
                                achievement.at("ID"));
}

bool AchievementSystem::isUnlocked(AchievementIDs id) const
{
    return achievements.at(id).isUnlocked();
}

void AchievementSystem::unlock(AchievementIDs id)
{
    achievements.at(id).unlock();
}

std::vector<std::pair<AchievementIDs, bool>> AchievementSystem::getData() const
{
    std::vector<std::pair<AchievementIDs, bool>> result;
    result.reserve(achievements.size());
    for (const auto &[id, val] : achievements)
    {
        result.emplace_back(id, val.isUnlocked());
    }
    return result;
}

void AchievementSystem::loadData(
    const std::vector<std::pair<AchievementIDs, bool>> &data)
{
    for (const auto &[id, unlockedState] : data)
    {
        achievements[id].setState(unlockedState);
    }
}

void AchievementSystem::checkAchievements()
{
    for (const auto &[id, _] : achievements)
    {
        if (isUnlocked(id))
            continue;

        if (achievements.at(id).unlockConditionMet())
        {
            unlock(id);
            pushNotification(id);
        }
    }
}

bool AchievementSystem::isUnlocked(BuildingType bType) const
{
    if (const auto ach = idMaps.buildings.find(bType);
        ach != idMaps.buildings.end())
    {
        return achievements.at(ach->second).isUnlocked();
    }
    return true;
}

bool AchievementSystem::isUnlocked(JellyJob jJob) const
{
    if (idMaps.jobs.contains(jJob))
        return achievements.at(idMaps.jobs.at(jJob)).isUnlocked();
    return false;
}

bool AchievementSystem::isUnlocked(RessourceType rType) const
{

    if (const auto ach = idMaps.ressources.find(rType);
        ach != idMaps.ressources.end())
    {
        return achievements.at(ach->second).isUnlocked();
    }
    return true;
}

bool AchievementSystem::isUnlocked(AbilityType abiType) const
{
    if (const auto ach = idMaps.abilities.find(abiType);
        ach != idMaps.abilities.end())
    {
        return achievements.at(ach->second).isUnlocked();
    }
    return true;
}

bool AchievementSystem::isUnlocked(UpgradeID id) const
{
    if (idMaps.upgrades.contains(id))
        return achievements.at(idMaps.upgrades.at(id)).isUnlocked();
    return false;
}

bool AchievementSystem::isUnlocked(AquaCultureID id) const
{
    if (idMaps.cultures.contains(id))
        return achievements.at(idMaps.cultures.at(id)).isUnlocked();
    return false;
}

std::optional<std::string_view> AchievementSystem::getNotification() const
{
    if (!notificationQueue.empty())
        return notificationQueue.front().getNotificationText();

    return std::nullopt;
}

void AchievementSystem::popNotification()
{
    notificationQueue.pop();
}

void AchievementSystem::pushNotification(AchievementIDs id)
{
    if (const auto it = notifications.find(id); it != notifications.end())
        notificationQueue.push(it->second);
}

std::span<const AchievementIDs> AchievementSystem::getAchievementsIDs() const
{
    return idMaps.allAchievementsIDs;
}

std::span<const std::tuple<AchievementIDs, unsigned, std::string, std::string>>
AchievementSystem::getDepthRewards() const
{
    return depthRewards;
}
