#pragma once
#include "GameIDsTypes.hpp"
#include "Questline.hpp"
#include "SaveAndLoadable.hpp"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct QuestSaveData
{
    std::vector<std::pair<QuestLineEnum, unsigned>> questsProgress;
};

class QuestManager
    : private SaveAndLoadable<std::vector<std::pair<QuestLineEnum, unsigned>>>
{
  public:
    virtual ~QuestManager() = default;
    QuestManager();

    QuestManager(const QuestManager &) = delete;
    QuestManager(QuestManager &&) = delete;
    QuestManager &operator=(const QuestManager &) = delete;
    QuestManager &operator=(QuestManager &&) = delete;

    void completeQuest(QuestLineEnum);
    bool isComplete(QuestLineEnum, unsigned) const;

    std::string getCurrentQuestText(QuestLineEnum) const;

    std::vector<std::pair<RessourceType, double>> getCurrentQuestRequirements(
        QuestLineEnum) const;
    std::vector<std::pair<QuestLineEnum, unsigned>> getData() const override;
    void loadData(
        const std::vector<std::pair<QuestLineEnum, unsigned>> &data) override;

  private:
    std::unordered_map<QuestLineEnum, Questline> questlines;
};
