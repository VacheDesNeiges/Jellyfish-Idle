#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Building : public GameDataAccess
{
  public:
    Building() = default;
    explicit Building(const nlohmann::json &);

    void buy();
    void update();

    void setQuantity(unsigned);
    unsigned getCurrentQuantity() const;
    unsigned getIncreaseToMaxJfish() const;
    std::string getBuildingName() const;

    std::vector<std::pair<RessourceType, double>> getProdPerTick() const;
    std::vector<std::pair<RessourceType, double>> getConsumPerTick() const;
    std::vector<std::pair<RessourceType, double>> getNextBuyCost() const;

    std::span<const std::pair<RessourceType, double>> getIncreasedStorage()
        const;

    std::string getDescription() const;

  private:
    std::string name;
    std::string description;
    unsigned quantity = 0;
    unsigned increaseToMaxJfish = 0;
    double priceMultiplier = 1;
    std::vector<std::pair<RessourceType, double>> basePrice;
    std::unordered_map<RessourceType, double> baseProductionPerTick;
    std::unordered_map<RessourceType, double> baseConsumptionPerTick;
    std::unordered_map<RessourceType, double> baseIncreasedStorage;

    std::vector<std::pair<RessourceType, double>> prodPerTick;
    std::vector<std::pair<RessourceType, double>> consumPerTick;
    std::vector<std::pair<RessourceType, double>> increasedStorage;
};
