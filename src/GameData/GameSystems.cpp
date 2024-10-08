#include "GameSystems.hpp"

#include "GameDataAccess.hpp"
#include "GameDataView.hpp"
#include "GameSynchronizer.hpp"
#include "GardenManager.hpp"
#include "InputHandler.hpp"

#include "QuestManager.hpp"
#include "SaveSystem.hpp"
#include <memory>
#include <string>

GameSystems::GameSystems()
{
    systems->ressources = std::make_shared<RessourceManager>();
    systems->buildings = std::make_shared<BuildingManager>();
    systems->jellies = std::make_shared<JellyfishManager>();
    systems->achievements = std::make_shared<AchievementSystem>();
    systems->abilities = std::make_shared<AbilityManager>();
    systems->depth = std::make_shared<DepthSystem>();
    systems->upgrades = std::make_shared<UpgradeManager>();
    systems->multipliers = std::make_shared<MultipliersRegister>();
    systems->crafts = std::make_shared<CraftingManager>();
    systems->garden = std::make_shared<GardenManager>();
    systems->quests = std::make_shared<QuestManager>();

    dataView = std::make_shared<GameDataView>(systems);
    GameDataAccess::bindDataView(dataView);

    inputHandler = std::make_shared<InputHandler>(systems);
    synchronizer = std::make_unique<GameSynchronizer>(systems);
}

void GameSystems::save() const
{
    SaveData data;
    data.buildings = systems->buildings->getData();
    data.achievements = systems->achievements->getData();
    data.ressources = systems->ressources->getData();
    data.jellies = systems->jellies->getData();
    data.depth = systems->depth->getData();
    data.upgrades = systems->upgrades->getData();
    data.crafts = systems->crafts->getData();
    data.cultures = systems->garden->getData();
    data.quests = systems->quests->getData();

    SaveSystem::save(data);
}

void GameSystems::loadSave(const std::string &path) const
{
    auto loadedData = SaveSystem::loadFromFile(path);
    systems->buildings->loadData(loadedData.buildings);
    systems->achievements->loadData(loadedData.achievements);
    systems->jellies->loadData(loadedData.jellies);
    systems->depth->loadData(loadedData.depth);
    systems->upgrades->loadData(loadedData.upgrades);
    systems->garden->loadData(loadedData.cultures);
    systems->quests->loadData(loadedData.quests);

    synchronizer->synchronizeSystems();

    systems->ressources->loadData(loadedData.ressources);
    systems->crafts->loadData(loadedData.crafts);
}

std::shared_ptr<GameDataView> GameSystems::getDataView() const
{
    return dataView;
}

std::shared_ptr<InputHandler> GameSystems::getInputHandler() const
{
    return inputHandler;
}

void GameSystems::gameTick() const
{
    synchronizer->gameTick();
}
