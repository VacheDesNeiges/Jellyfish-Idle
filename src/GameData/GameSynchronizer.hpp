#pragma once
#include "GameIDsTypes.hpp"

#include <memory>
#include <unordered_map>

struct SystemPtrs;

class GameSynchronizer
{
  public:
    explicit GameSynchronizer(std::shared_ptr<SystemPtrs>);

    void gameTick() const;
    void synchronizeSystems() const;

  private:
    std::shared_ptr<SystemPtrs> systems;

    void checkAchievements() const;
    void distributeExp() const;
    void convertRessources() const;

    std::unordered_map<RessourceType, double> addMaps(
        const std::unordered_map<RessourceType, double> &,
        const std::unordered_map<RessourceType, double> &) const;
};