#include "Achievement.hpp"
#include "GameIDsTypes.hpp"

#include <algorithm>
#include <nlohmann/json.hpp>

Achievement::Achievement(const nlohmann::json &json)
{
    for (const auto &condition : json.at("Condition"))
    {

        if (condition.contains("Job"))
        {
            jobsCondition.emplace_back(JellyJob{condition.at("Job")},
                                       condition.at("NumAssigned"));
            continue;
        }

        if (condition.contains("NumJfish"))
        {
            jfishNumCondition = condition.at("NumJfish");
            continue;
        }

        if (condition.contains("Depth"))
        {
            depthCondition = condition.at("Depth");
            continue;
        }

        if (condition.contains("AchievementID"))
        {
            achievementsCondition.emplace_back(condition.at("AchievementID"));
            continue;
        }

        if (condition.contains("UpgradeID"))
        {
            upgradeCondition.emplace_back(condition.at("UpgradeID"));
            continue;
        }

        if (condition.contains("RessourceID"))
        {
            ressourceCondition.emplace_back(condition.at("RessourceID"),
                                            condition.at("Quantity_GT"));
            continue;
        }

        if (condition.contains("BuildingID"))
        {
            buildingsCondition.emplace_back(condition.at("BuildingID"),
                                            condition.at("MinQuantity"));
            continue;
        }
        if (condition.contains("AnyOf"))
        {
            if (condition.at("AnyOf") == "Rare")
            {
                anyRareRessource = true;
            }
            else if (condition.at("AnyOf") == "Manufactured")
            {
                AnyManufacturedRessource = true;
            }
            continue;
        }
        if (condition.contains("Questline"))
        {
            questCondition.emplace_back(
                static_cast<QuestLineEnum>(condition.at("Questline")),
                condition.at("QuestNumber"));
            continue;
        }
    }
}

bool Achievement::isUnlocked() const
{
    return unlocked;
}

void Achievement::unlock()
{
    unlocked = true;
}

void Achievement::setState(bool newState)
{
    unlocked = newState;
}

bool Achievement::ressourcesConditionsMet() const
{
    return std::ranges::all_of(ressourceCondition, [this](const auto &pair) {
        const auto &[rType, requirement] = pair;
        return ressourcesView()->getRessourceQuantity(rType) > requirement;
    });
}

bool Achievement::buildingConditionsMet() const
{
    return std::ranges::all_of(buildingsCondition, [this](const auto &pair) {
        const auto &[bType, requirement] = pair;
        return buildingsView()->getBuildingQuantity(bType) >= requirement;
    });
}

bool Achievement::achievementConditionsMet() const
{
    return std::ranges::all_of(achievementsCondition, [this](const auto &ach) {
        return achievementsView()->isUnlocked(ach);
    });
}

bool Achievement::jobsConditionsMet() const
{
    return std::ranges::all_of(jobsCondition, [this](const auto &pair) {
        const auto &[job, numRequired] = pair;
        return jelliesView()->getNumJellies(job) >= numRequired;
    });
}

bool Achievement::upgradeConditionMet() const
{
    return std::ranges::all_of(upgradeCondition, [this](const auto &upgrID) {
        return upgradeView()->isBought(upgrID);
    });
}

bool Achievement::questConditionMet() const
{
    return std::ranges::all_of(questCondition, [this](const auto &pair) {
        const auto &[ql, qnum] = pair;
        return questsView()->isComplete(ql, qnum);
    });
}

bool Achievement::unlockConditionMet() const
{
    if (jelliesView()->getNumJellies() < jfishNumCondition)
        return false;

    if (depthCondition > depthView()->getCurrentDepth())
        return false;

    if (!ressourceCondition.empty() && !ressourcesConditionsMet())
        return false;

    if (!buildingsCondition.empty() && !buildingConditionsMet())
        return false;

    if (!achievementsCondition.empty() && !achievementConditionsMet())
        return false;

    if (!jobsCondition.empty() && !jobsConditionsMet())
        return false;

    if (!upgradeCondition.empty() && !upgradeConditionMet())
        return false;

    if (anyRareRessource)
    {
        if (std::ranges::all_of(
                ressourcesView()->getRareRessourceTypes(),
                [this](const auto &rType) {
                    return ressourcesView()->getRessourceQuantity(rType) == 0;
                }))
        {
            return false;
        }
    }

    if (AnyManufacturedRessource)
    {
        if (std::ranges::all_of(
                ressourcesView()->getCraftableRessourceTypes(),
                [this](const auto &rType) {
                    return ressourcesView()->getRessourceQuantity(rType) == 0;
                }))
        {
            return false;
        }
    }

    if (!questCondition.empty() && !questConditionMet())
    {
        return false;
    }

    return true;
}
