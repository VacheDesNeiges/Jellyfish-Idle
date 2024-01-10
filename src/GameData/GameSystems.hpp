#pragma once

#include "GameSynchronizer.hpp"
#include "InputHandler.hpp"
#include <functional>
#include <map>
#include <memory>

class GameDataView;
class GameSynchronizer;
class InputHandler;

class RessourceManager;
class BuildingManager;
class JellyfishManager;
class AchievementSystem;
class AbilityManager;
class DepthSystem;
class UpgradeManager;
class MultipliersRegister;

struct SystemPtrs
{
  std::shared_ptr<RessourceManager> ressources;
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<JellyfishManager> jellies;
  std::shared_ptr<AchievementSystem> achievements;
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<DepthSystem> depth;
  std::shared_ptr<UpgradeManager> upgrades;
  std::shared_ptr<MultipliersRegister> multipliers;
};

class GameSystems
{

public:
  GameSystems ();

  void save () const;
  void loadSave (const std::string &) const;
  void gameTick () const;

  std::shared_ptr<GameDataView> getDataView () const;
  std::shared_ptr<InputHandler> getInputHandler () const;

private:
  std::shared_ptr<SystemPtrs> systems;

  std::unique_ptr<GameSynchronizer> synchronizer;
  std::shared_ptr<GameDataView> dataView;
  std::shared_ptr<InputHandler>
      inputHandler; // might not be used here, instead return a unique_ptr from
                    // the function
};