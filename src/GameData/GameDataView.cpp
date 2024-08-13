#include "GameDataView.hpp"

#include "AbilityDataView.hpp"
#include "AchievementDataView.hpp"
#include "BuildingDataView.hpp"
#include "CraftingDataView.hpp"
#include "DepthDataView.hpp"
#include "GardenDataView.hpp"
#include "JellyfishDataView.hpp"
#include "MultiplierDataView.hpp"
#include "QuestDataView.hpp"
#include "RessourceDataView.hpp"
#include "UpgradeDataView.hpp"

#include "GameSystems.hpp"

#include <memory>

GameDataView::GameDataView(std::shared_ptr<SystemPtrs> s) : systems(s)

{
    ressourcesView =
        std::make_shared<const RessourceDataView>(systems->ressources);
    buildingsView = std::make_shared<const BuildingDataView>(
        systems->buildings, systems->ressources);
    jelliesView = std::make_shared<const JellyFishDataView>(systems->jellies);
    achievementsView =
        std::make_shared<const AchievementDataView>(systems->achievements);
    abilitiesView = std::make_shared<const AbilityDataView>(
        systems->abilities, systems->ressources);
    depthView = std::make_shared<const DepthDataView>(systems->depth);
    upgradesView = std::make_shared<const UpgradeDataView>(systems->upgrades,
                                                           systems->ressources);
    multipliersView =
        std::make_shared<const MultiplierDataView>(systems->multipliers);
    craftView = std::make_shared<const CraftDataView>(systems->crafts);
    gardenView = std::make_shared<const GardenDataView>(systems->garden);
    questsView = std::make_shared<const QuestDataView>(systems->quests);
}

std::shared_ptr<const RessourceDataView> GameDataView::getRessourcesView() const
{
    return ressourcesView;
}

std::shared_ptr<const BuildingDataView> GameDataView::getBuildingsView() const
{
    return buildingsView;
}

std::shared_ptr<const JellyFishDataView> GameDataView::getJelliesView() const
{
    return jelliesView;
}

std::shared_ptr<const AchievementDataView> GameDataView::getAchievementsView()
    const
{
    return achievementsView;
}

std::shared_ptr<const AbilityDataView> GameDataView::getAbilitiesView() const
{
    return abilitiesView;
}

std::shared_ptr<const DepthDataView> GameDataView::getDepthView() const
{
    return depthView;
}

std::shared_ptr<const UpgradeDataView> GameDataView::getUpgradeView() const
{
    return upgradesView;
}

std::shared_ptr<const MultiplierDataView> GameDataView::getMultiplierView()
    const
{
    return multipliersView;
}

std::shared_ptr<const CraftDataView> GameDataView::getCraftView() const
{
    return craftView;
}

std::shared_ptr<const GardenDataView> GameDataView::getGardenView() const
{
    return gardenView;
}

std::shared_ptr<const QuestDataView> GameDataView::getQuestsView() const
{
    return questsView;
}