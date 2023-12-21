#pragma once

#include "Building.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"

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
                std::shared_ptr<AbilityManager>);

  void gatherFood ();
  void buy (BuildingType);

  bool unassignJelly (JellyJobs);
  bool assignJelly (JellyJobs);

  void useAbility (AbilityType);

private:
  std::shared_ptr<RessourceManager> ressources;
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<JellyfishManager> jellies;
  std::shared_ptr<AbilityManager> abilities;

  void updateMaxNumJellies ();
};