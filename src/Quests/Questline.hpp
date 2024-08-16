#include "GameIDsTypes.hpp"
#include "Quest.hpp"
#include <nlohmann/json.hpp>
#include <vector>

class Questline
{
  public:
    explicit Questline(const nlohmann::json &);
    void completeQuest();
    bool isComplete(unsigned) const;
    std::string getCurrentQuestText() const;
    void setCurrentQuest(unsigned);
    unsigned getCurrentQuestIndex() const;
    std::vector<std::pair<RessourceType, double>> getCurrentQuestRequirements()
        const;

  private:
    unsigned currentQuest = 0;
    std::vector<Quest> quests;
};
