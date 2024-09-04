#include "QuestDataView.hpp"
#include "GameIDsTypes.hpp"
#include "QuestManager.hpp"
#include <memory>
#include <string>

QuestDataView::QuestDataView(std::shared_ptr<QuestManager> qManager)
    : quests(qManager)
{
}

std::string QuestDataView::getCurrentQuestText(QuestLineEnum questline) const
{
    return quests->getCurrentQuestText(questline);
}

std::vector<std::pair<RessourceType, double>> QuestDataView::
    getCurrentQuestRequirements(QuestLineEnum ql) const
{
    return quests->getCurrentQuestRequirements(ql);
}

bool QuestDataView::isComplete(QuestLineEnum ql, unsigned qnum) const
{
    return quests->isComplete(ql, qnum);
}
