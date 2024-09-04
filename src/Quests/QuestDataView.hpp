#pragma once

#include "GameIDsTypes.hpp"
#include "QuestManager.hpp"
#include <memory>

class QuestDataView
{
  public:
    explicit QuestDataView(const std::shared_ptr<QuestManager> &);
    std::string getCurrentQuestText(QuestLineEnum) const;
    bool isComplete(QuestLineEnum, unsigned) const;

    std::vector<std::pair<RessourceType, double>> getCurrentQuestRequirements(
        QuestLineEnum) const;

  private:
    std::shared_ptr<const QuestManager> quests;
};
