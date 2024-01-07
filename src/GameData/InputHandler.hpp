#pragma once

#include "AbilityManager.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "RessourceManager.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include <memory>

class RessourceManager;
class JellyfishManager;
class BuildingManager;
class AbilityManager;

class InputHandler
{
public:
  InputHandler (std::shared_ptr<RessourceManager>,
                std::shared_ptr<BuildingManager>,
                std::shared_ptr<JellyfishManager>,
                std::shared_ptr<AbilityManager>,
                std::shared_ptr<UpgradeManager>);

  void gatherFood ();
  void buy (BuildingType);
  void buy (UpgradeID);

  bool unassignJelly (JellyJobs);
  bool assignJelly (JellyJobs);

  void useAbility (AbilityType);

private:
  std::shared_ptr<RessourceManager> ressources;
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<JellyfishManager> jellies;
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<UpgradeManager> upgrades;

  void updateMaxNumJellies ();
};