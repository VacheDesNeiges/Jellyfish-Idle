#include "GameSystems.hpp"
#include "DepthSystem.hpp"
#include "GameDataView.hpp"
#include "GameSynchronizer.hpp"
#include "InputHandler.hpp"
#include "SaveSystem.hpp"
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

  dataView = std::make_shared<GameDataView> (ressources, buildings, jellies,
                                             achievements, abilities, depth);
  inputHandler = std::make_shared<InputHandler> (ressources, buildings,
                                                 jellies, abilities);

  synchronizer = std::make_unique<GameSynchronizer> (
      ressources, buildings, jellies, achievements, abilities, depth);
}

void
GameSystems::save () const
{
  SaveSystem::save (buildings->getData (), achievements->getData (),
                    ressources->getData (), jellies->getData (),
                    depth->getData ());
  // TODO : refactor to use a SaveData object instead ?
}

void
GameSystems::loadSave (std::string path)
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
GameSystems::getDataView ()
{
  return std::make_shared<GameDataView> (*dataView);
}

std::shared_ptr<InputHandler>
GameSystems::getInputHandler ()
{
  return std::make_shared<InputHandler> (*inputHandler);
}

void
GameSystems::gameTick ()
{
  synchronizer->gameTick ();
}