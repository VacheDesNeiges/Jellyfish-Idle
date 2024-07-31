#pragma once

#include "GameIDsTypes.hpp"
#include "QuestManager.hpp"
#include <memory>

class QuestDataView
{
public:
  explicit QuestDataView (std::shared_ptr<QuestManager>);
  std::string getCurrentQuestText (QuestLineEnum) const;

private:
  std::shared_ptr<const QuestManager> quests;
};