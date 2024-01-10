#pragma once
#include "GameSystems.hpp"
#include <memory>

class RessourceManager;
class JellyfishManager;
class BuildingManager;
class AbilityManager;
class UpgradeManager;
enum class BuildingType;
enum class JellyJobs;
enum class AbilityType;
enum class UpgradeID;

class InputHandler
{
public:
  InputHandler (std::shared_ptr<RessourceManager>,
                std::shared_ptr<BuildingManager>,
                std::shared_ptr<JellyfishManager>,
                std::shared_ptr<AbilityManager>,
                std::shared_ptr<UpgradeManager>);

  void gatherFood () const;
  void buy (BuildingType) const;
  void buy (UpgradeID) const;

  bool unassignJelly (JellyJobs) const;
  bool assignJelly (JellyJobs) const;

  void useAbility (AbilityType) const;

private:
  std::shared_ptr<RessourceManager> ressources;
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<JellyfishManager> jellies;
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<UpgradeManager> upgrades;

  void updateMaxNumJellies () const;
};