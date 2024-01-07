#include "GameSystems.hpp"
#include "DepthSystem.hpp"
#include "GameDataAccess.hpp"
#include "GameDataView.hpp"
#include "GameSynchronizer.hpp"
#include "InputHandler.hpp"
#include "SaveSystem.hpp"
#include "UpgradeManager.hpp"
#include <memory>
#include <string>

GameSystems::GameSystems ()
{
  ressources = std::make_shared<RessourceManager> ();
  buildings = std::make_shared<BuildingManager> ();
  jellies = std::make_shared<JellyfishManager> ();
  achievements = std::make_shared<AchievementSystem> ();
  abilities = std::make_shared<AbilityManager> ();
  depth = std::make_shared<DepthSystem> ();
  upgrades = std::make_shared<UpgradeManager> ();

  dataView = std::make_shared<GameDataView> (ressources, buildings, jellies,
                                             achievements, abilities, depth,
                                             upgrades);

  GameDataAccess::bindDataView (dataView);

  inputHandler = std::make_shared<InputHandler> (ressources, buildings,
                                                 jellies, abilities, upgrades);

  synchronizer = std::make_unique<GameSynchronizer> (
      ressources, buildings, jellies, achievements, abilities, depth,
      upgrades);
}

void
GameSystems::save () const
{
  SaveData data;
  data.buildings = buildings->getData ();
  data.achievements = achievements->getData ();
  data.ressources = ressources->getData ();
  data.jellies = jellies->getData ();
  data.depth = depth->getData ();

  SaveSystem::save (data);
}

void
GameSystems::loadSave (const std::string &path) const
{
  auto loadedData = SaveSystem::loadFromFile (path);
  buildings->loadData (loadedData.buildings);
  achievements->loadData (loadedData.achievements);
  ressources->loadData (loadedData.ressources);
  jellies->loadData (loadedData.jellies);
  depth->loadData (loadedData.depth);
  synchronizer->update ();
}

std::shared_ptr<GameDataView>
GameSystems::getDataView () const
{
  return dataView;
}

std::shared_ptr<InputHandler>
GameSystems::getInputHandler () const
{
  return inputHandler;
}

void
GameSystems::gameTick () const
{
  synchronizer->gameTick ();
}