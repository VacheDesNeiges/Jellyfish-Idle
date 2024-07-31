#include "QuestDataView.hpp"
#include "GameIDsTypes.hpp"
#include "QuestManager.hpp"
#include <memory>
#include <string>

QuestDataView::QuestDataView (std::shared_ptr<QuestManager> q) : quests (q) {}

std::string
QuestDataView::getCurrentQuestText (QuestLineEnum questline) const
{
  return quests->getCurrentQuestText (questline);
}