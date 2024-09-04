#pragma once
#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class InsightAbility : public GameDataAccess
{
  public:
    explicit InsightAbility(const nlohmann::json &);
    std::string getDescription() const;
    std::string getName() const;
    std::vector<std::pair<RessourceType, double>> getCost() const;
    std::vector<std::pair<RessourceType, double>> getProduction() const;

  private:
    std::string name;
    std::string description;
    std::vector<std::pair<RessourceType, double>> castingCost;
    std::vector<std::pair<RessourceType, double>> baseRessourcesGained;

    friend class CallThunder;
};
