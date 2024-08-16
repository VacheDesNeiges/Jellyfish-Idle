#include "QuestManager.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <vector>

QuestManager::QuestManager()
{
    auto fstream = FilePaths::getFileStream(FilePaths::QuestsPath);
    try
    {
        auto questsJson = nlohmann::json::parse(fstream);
        questlines.reserve(questsJson.at("Questlines").size());

        for (const auto &ql : questsJson.at("Questlines"))
        {
            if (ql.at("Name") == "OctopusQuests")
            {
                questlines.try_emplace(QuestLineEnum::Octopus, ql);
            }
            else
            {
                questlines.try_emplace(QuestLineEnum::Whale, ql);
            }
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing quests :\n" << e.what() << '\n';
        abort();
    }
}

std::string QuestManager::getCurrentQuestText(QuestLineEnum ql) const
{
    return questlines.at(ql).getCurrentQuestText();
}

std::vector<std::pair<RessourceType, double>> QuestManager::
    getCurrentQuestRequirements(QuestLineEnum ql) const
{
    return questlines.at(ql).getCurrentQuestRequirements();
}

void QuestManager::completeQuest(QuestLineEnum ql)
{
    questlines.at(ql).completeQuest();
}

void QuestManager::loadData(
    const std::vector<std::pair<QuestLineEnum, unsigned>> &vec)
{
    for (const auto &[ql, currentQuest] : vec)
    {
        questlines.at(ql).setCurrentQuest(currentQuest);
    }
}

std::vector<std::pair<QuestLineEnum, unsigned>> QuestManager::getData() const
{
    std::vector<std::pair<QuestLineEnum, unsigned>> ret;
    for (const auto &[qlenum, ql] : questlines)
    {
        ret.emplace_back(qlenum, ql.getCurrentQuestIndex());
    }
    return ret;
}

bool QuestManager::isComplete(QuestLineEnum ql, unsigned qnum) const
{
    return questlines.at(ql).isComplete(qnum);
}
