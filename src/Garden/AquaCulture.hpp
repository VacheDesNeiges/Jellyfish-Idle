#pragma once

#include "GameIDsTypes.hpp"
#include "SaveAndLoadable.hpp"

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <utility>
#include <vector>

struct CultureData
{
    bool craftOngoing;
    unsigned fieldCount;
};

class AquaCulture final : public SaveAndLoadable<CultureData>
{
  public:
    AquaCulture() = default;
    explicit AquaCulture(const nlohmann::json &);
    ~AquaCulture() = default;

    AquaCulture(const AquaCulture &) = delete;
    AquaCulture(AquaCulture &&) = delete;
    AquaCulture &operator=(const AquaCulture &) = delete;
    AquaCulture &operator=(AquaCulture &&) = delete;

    void start();
    void cancel();
    bool isOngoing() const;
    std::string getName() const;

    std::vector<std::pair<RessourceType, double>> getBaseConsumption() const;
    std::vector<std::pair<RessourceType, double>> getBaseProduction() const;

    CultureData getData() const override;
    void loadData(const CultureData &) override;

  private:
    bool cultureOngoing = false;
    std::string name;

    std::vector<std::pair<RessourceType, double>> baseProduction;
    std::vector<std::pair<RessourceType, double>> baseConsumption;
};
