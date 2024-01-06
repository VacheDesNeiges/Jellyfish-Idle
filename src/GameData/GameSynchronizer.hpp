#pragma once
#include "DepthSystem.hpp"
#include "GameDataView.hpp"
#include "Ressource.hpp"
#include "UpgradeManager.hpp"
#include <map>
#include <memory>

class RessourceManager;
class BuildingManager;
class JellyfishManager;
class AbilityManager;

class GameSynchronizer
{
public:
  GameSynchronizer (std::shared_ptr<RessourceManager>,
                    std::shared_ptr<BuildingManager>,
                    std::shared_ptr<JellyfishManager>,
                    std::shared_ptr<AchievementSystem>,
                    std::shared_ptr<AbilityManager>,
                    std::shared_ptr<DepthSystem>,
                    std::shared_ptr<UpgradeManager>);

  void gameTick () const;
  void update () const;

private:
  std::shared_ptr<RessourceManager> ressources;
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<JellyfishManager> jellies;
  std::shared_ptr<AchievementSystem> achievements;
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<DepthSystem> depth;
  std::shared_ptr<UpgradeManager> upgrades;

  void checkAchievements () const;
  void checkJellyfishArrival () const;

  std::map<RessourceType, double>
  addMaps (const std::map<RessourceType, double> &,
           const std::map<RessourceType, double> &) const;
};