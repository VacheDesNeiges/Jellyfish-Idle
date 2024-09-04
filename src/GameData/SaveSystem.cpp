#include "SaveSystem.hpp"

#include "AquaCulture.hpp"
#include "CraftingRecipe.hpp"
#include "DepthSystem.hpp"
#include "GameIDsTypes.hpp"
#include "JellyfishManager.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

void SaveSystem::save(const SaveData &data)
{
    nlohmann::json json;
    for (const auto &[type, quant] : data.buildings)
    {
        json["Building"] +=
            {{"id", static_cast<int>(type)}, {"Quantity", quant}};
    }

    for (const auto &[idAch, isUnlocked] : data.achievements)
    {
        json["Achievement"] +=
            {{"id", static_cast<int>(idAch)}, {"Unlocked", isUnlocked}};
    }

    for (const auto &[idRes, quant] : data.ressources)
    {
        json["Ressource"] +=
            {{"id", static_cast<int>(idRes)}, {"Quantity", quant}};
    }

    json["Jellies"] = {
        {"num", data.jellies.numJellies},
        {"numMax", data.jellies.maxNumJellies},
        {"Jobs", nlohmann::json::array()},
    };

    try
    {
        for (const auto &[jobID, num] : data.jellies.jobNumbers)
        {
            json["Jellies"]["Jobs"].push_back(
                {{"id", int(jobID)}, {"num", num}});
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while writting jellies :\n" << e.what() << '\n';
    }

    json["Depth"] += {
        {"currentDepth", data.depth.currentDepth},
        {"currentProg", data.depth.currentProg},
    };

    for (const auto &[id, val] : data.upgrades)
    {
        json["Upgrade"] += {
            {"id", static_cast<int>(id)},
            {"Bought", val},
        };
    }

    for (const auto &[id, craftData] : data.crafts)
    {
        json["Craft"] += {
            {"id", static_cast<int>(id)},
            {"Workers", craftData.numAssignedWorkers},
            {"Done", craftData.craftDone},
            {"Ongoing", craftData.craftOngoing},
            {"KeepCraftingMode", craftData.keepCraftingEnabled},
            {"RemainingTicks", craftData.remainingTicksToCraft},
            {"Level", craftData.lvl},
            {"CurrentProg", craftData.progressNeeded},
        };
    }

    for (const auto &[id, cultureData] : data.cultures)
    {
        json["Culture"] += {
            {"id", static_cast<int>(id)},
            {"Fields", cultureData.fieldCount},
            {"Ongoing", cultureData.craftOngoing},
        };
    }

    for (const auto &[ql, index] : data.quests)
    {
        json["Quests"] += {
            {"QuestLine", static_cast<int>(ql)},
            {"CurrentQuest", index},
        };
    }

    std::ofstream file(saveFileName);
    file << json;
}

SaveData SaveSystem::loadFromFile(std::string path)
{
    SaveData result;
    path += "/" + saveFileName;

    std::ifstream filestream(path);

    nlohmann::json data;

    try
    {
        data = nlohmann::json::parse(filestream);
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing save with json::parse() :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {

        result.buildings.reserve(data.at("Building").size());
        for (const auto &buildingData : data["Building"])
        {
            result.buildings.emplace_back(
                static_cast<BuildingType>(buildingData["id"].get<int>()),
                buildingData["Quantity"].get<unsigned>());
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved buildings :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {

        result.achievements.reserve(data.at("Achievement").size());
        for (const auto &achievementData : data["Achievement"])
        {
            result.achievements.emplace_back(
                static_cast<AchievementIDs>(achievementData["id"].get<int>()),
                achievementData["Unlocked"].get<bool>());
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved buildings :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {
        result.ressources.reserve(data.at("Ressource").size());
        for (const auto &ressourceData : data["Ressource"])
        {
            result.ressources.emplace_back(
                static_cast<RessourceType>(ressourceData["id"].get<int>()),
                ressourceData["Quantity"].get<double>());
        }
    }

    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved achievements :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {
        result.jellies.numJellies =
            data.at("Jellies").at("num").get<unsigned>();
        result.jellies.maxNumJellies =
            data.at("Jellies").at("numMax").get<unsigned>();

        for (const auto &job : data.at("Jellies").at("Jobs"))
        {
            result.jellies.jobNumbers.emplace_back(
                JellyJob(job.at("id").get<int>()),
                job.at("num").get<unsigned>());
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved jellies & jobs :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {

        result.depth.currentDepth =
            data["Depth"][0]["currentDepth"].get<unsigned>();
        result.depth.currentProg = data["Depth"][0]["currentProg"].get<float>();
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved depth :\n" << e.what() << '\n';
        abort();
    }

    try
    {
        result.upgrades.reserve(data.at("Upgrade").size());
        for (const auto &upgradeData : data["Upgrade"])
        {
            result.upgrades.emplace_back(
                static_cast<UpgradeID>(upgradeData["id"].get<int>()),
                upgradeData["Bought"].get<bool>());
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved upgrades :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {
        result.crafts.reserve(data.at("Craft").size());
        for (const auto &craftData : data["Craft"])
        {
            result.crafts.emplace_back(
                static_cast<RecipeID>(craftData["id"].get<int>()),
                RecipeSaveData{
                    craftData["Level"].get<unsigned>(),
                    craftData["CurrentProg"].get<double>(),
                    0,
                    craftData["Ongoing"].get<bool>(),
                    craftData["Done"].get<bool>(),
                    craftData["KeepCraftingMode"].get<bool>(),
                    craftData["RemainingTicks"].get<unsigned>(),
                    craftData["Workers"].get<unsigned>(),
                });
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved crafts :\n" << e.what() << '\n';
        abort();
    }

    try
    {
        result.cultures.reserve(data.at("Culture").size());
        for (const auto &cultureData : data["Culture"])
        {
            result.cultures.emplace_back(
                static_cast<AquaCultureID>(cultureData["id"].get<int>()),
                CultureData{
                    cultureData["Ongoing"].get<bool>(),
                    cultureData["Fields"].get<unsigned>(),
                });
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved cultures :\n"
                  << e.what() << '\n';
        abort();
    }

    try
    {
        result.quests.reserve(data.at("Quests").size());
        for (const auto &questData : data["Quests"])
        {
            result.quests.emplace_back(
                static_cast<QuestLineEnum>(
                    questData["QuestLine"].get<unsigned>()),
                questData["CurrentQuest"].get<unsigned>());
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing saved quests :\n" << e.what() << '\n';
        abort();
    }

    return result;
}
