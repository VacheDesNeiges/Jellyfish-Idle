#pragma once
#include "GameIDsTypes.hpp"
#include "Questline.hpp"

#include <string>
#include <unordered_map>
#include <vector>

class QuestManager
{
  public:
    QuestManager();
    std::string getCurrentQuestText(QuestLineEnum) const;

    std::vector<std::pair<RessourceType, double>> getCurrentQuestRequirements(
        QuestLineEnum) const;

  private:
    std::unordered_map<QuestLineEnum, Questline> questlines;
};