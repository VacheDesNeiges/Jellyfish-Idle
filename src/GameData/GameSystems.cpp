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

  std::cout << "Managers building complete\n";

  dataView = std::make_shared<GameDataView> (ressources, buildings, jellies,
                                             achievements, abilities, depth);

  ressources->bindDataView (dataView);
  buildings->bindDataView (dataView);
  jellies->bindDataView (dataView);
  achievements->bindDataView (dataView);
  abilities->bindDataView (dataView);
  depth->bindDataView (dataView);

  std::cout << "DataView building complete\n";

  inputHandler = std::make_shared<InputHandler> (ressources, buildings,
                                                 jellies, abilities);
  std::cout << "InputHandler Building complete\n";

  synchronizer = std::make_unique<GameSynchronizer> (
      ressources, buildings, jellies, achievements, abilities, depth);
  std::cout << "Synchronizer building complete\n";
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
  return dataView;
}

std::shared_ptr<InputHandler>
GameSystems::getInputHandler ()
{
  return inputHandler;
}

void
GameSystems::gameTick ()
{
  synchronizer->gameTick ();
}