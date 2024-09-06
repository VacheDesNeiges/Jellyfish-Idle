#pragma once

#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"

#include "unordered_map"
#include <utility>
#include <vector>

class RessourceManager final
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<RessourceType, double>>>
{
  public:
    RessourceManager();
    ~RessourceManager() = default;
    RessourceManager(const RessourceManager &) = delete;
    RessourceManager(RessourceManager &&) = delete;
    RessourceManager &operator=(const RessourceManager &) = delete;
    RessourceManager &operator=(RessourceManager &&) = delete;

    void init();

    void gatherSand();
    double getCurrentQuantity(RessourceType) const;
    double getMaxQuantity(RessourceType) const;
    double getNetProduction(RessourceType) const;
    double getProduction(RessourceType) const;
    double getConsumption(RessourceType) const;
    std::string_view getName(RessourceType) const;

    void zerosValuePerTick();

    bool canAfford(const std::vector<std::pair<RessourceType, double>> &) const;

    void add(RessourceType, double);
    void add(const std::vector<std::pair<RessourceType, double>> &);
    void substract(const std::vector<std::pair<RessourceType, double>> &);

    void addToProdPerTick(RessourceType, double);

    void updateMaxRessourcesQuantities(
        const std::unordered_map<RessourceType, double> &);

    void recomputeMaxQuantities();

    void consume(const std::unordered_map<RessourceType, double> &);
    void produce(const std::unordered_map<RessourceType, double> &);
    void tryConvert(const std::vector<std::pair<RessourceType, double>> &,
                    const std::vector<std::pair<RessourceType, double>> &);

    std::vector<std::pair<RessourceType, double>> getData() const override;
    void loadData(
        const std::vector<std::pair<RessourceType, double>> &data) override;

    std::span<const RessourceType> getAllRessourceTypes() const;
    std::span<const RessourceType> getRegularRessourceTypes() const;
    std::span<const RessourceType> getRareRessourceTypes() const;
    std::span<const RessourceType> getCraftableRessourceTypes() const;

  private:
    std::unordered_map<RessourceType, Ressource> ressources;
    std::vector<RessourceType> allRessourceTypes;
    std::vector<RessourceType> regularRessourceTypes;
    std::vector<RessourceType> rareRessourceTypes;
    std::vector<RessourceType> craftableRessourceTypes;
};
