#pragma once
#include "GameIDsTypes.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

class Quest
{
  public:
    explicit Quest(const nlohmann::json &);
    void complete();
    bool isComplete() const;
    std::string getDialogue() const;

    std::vector<std::pair<RessourceType, double>> getRequestedRessources()
        const;

  private:
    bool completed = false;
    std::string dialogue;
    std::vector<std::pair<RessourceType, double>> requestedRessources;
};
