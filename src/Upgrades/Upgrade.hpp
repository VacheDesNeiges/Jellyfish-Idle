#pragma once

#include "GameIDsTypes.hpp"
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Upgrade
{
  public:
    Upgrade() = default;
    explicit Upgrade(const nlohmann::json &);

    bool isUnlocked() const;
    void unlock();
    std::string_view getName() const;
    std::string_view getDescription() const;
    const std::vector<std::pair<RessourceType, double>> &getCost() const;
    const std::optional<UpgradeID> &getDependency() const;

  private:
    bool bought{false};
    std::string name;
    std::string description;
    std::vector<std::pair<RessourceType, double>> cost;
    std::optional<UpgradeID> dependency;
};
