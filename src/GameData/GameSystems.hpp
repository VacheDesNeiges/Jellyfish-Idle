#pragma once
#include <memory>

#include "GameSynchronizer.hpp"
#include "GardenManager.hpp"
#include "InputHandler.hpp"

#include "AbilityManager.hpp"
#include "AchievementSystem.hpp"
#include "BuildingManager.hpp"
#include "CraftingManager.hpp"
#include "DepthSystem.hpp"
#include "JellyfishManager.hpp"
#include "MultipliersRegister.hpp"
#include "RessourceManager.hpp"
#include "UpgradeManager.hpp"

class GameDataView;
class GameSynchronizer;
class InputHandler;

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
  std::shared_ptr<CraftingManager> crafts;
  std::shared_ptr<GardenManager> garden;
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
  std::shared_ptr<SystemPtrs> systems = std::make_shared<SystemPtrs> ();

  std::unique_ptr<GameSynchronizer> synchronizer;
  std::shared_ptr<GameDataView> dataView;
  std::shared_ptr<InputHandler> inputHandler;
};