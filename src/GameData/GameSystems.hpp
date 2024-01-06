#pragma once
#include "AbilityManager.hpp"
#include "Achievement.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "GameDataView.hpp"
#include "GameSynchronizer.hpp"
#include "InputHandler.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "Ressource.hpp"
#include "RessourceManager.hpp"
#include <functional>
#include <map>
#include <memory>

#include "DepthSystem.hpp"
#include "UpgradeManager.hpp"

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
  // Game Systems
  std::shared_ptr<RessourceManager> ressources;
  std::shared_ptr<BuildingManager> buildings;
  std::shared_ptr<JellyfishManager> jellies;
  std::shared_ptr<AchievementSystem> achievements;
  std::shared_ptr<AbilityManager> abilities;
  std::shared_ptr<DepthSystem> depth;
  std::shared_ptr<UpgradeManager> upgrades;

  std::unique_ptr<GameSynchronizer> synchronizer;
  std::shared_ptr<GameDataView> dataView;
  std::shared_ptr<InputHandler>
      inputHandler; // might not be used here, instead return a unique_ptr from
                    // the function
};