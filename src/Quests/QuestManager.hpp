#pragma once
#include "GameIDsTypes.hpp"
#include "Questline.hpp"

#include <string>
#include <unordered_map>
#include <vector>

class QuestManager
{
public:
  QuestManager ();
  std::string getCurrentQuestText (QuestLineEnum);
  std::vector<std::pair<RessourceType, double> >
      getCurrentQuestRequirements (QuestLineEnum);

private:
  std::unordered_map<QuestLineEnum, Questline> questlines;
};