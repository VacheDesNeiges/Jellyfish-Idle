#include "BuildingDataView.hpp"

#include "BuildingManager.hpp"
#include "GameIDsTypes.hpp"
#include "RessourceManager.hpp"
#include <string>

BuildingDataView::BuildingDataView(
    const std::shared_ptr<BuildingManager> &bManager,
    const std::shared_ptr<RessourceManager> &rManager)
    : buildings(bManager), ressources(rManager)
{
}

bool BuildingDataView::isBuyable(BuildingType bType) const
{
    bool buyable = true;
    for (const auto &[ressource, price] : buildings->nextBuyCost(bType))
    {
        if (price > ressources->getCurrentQuantity(ressource))
            buyable = false;
    }
    return buyable;
}

std::string BuildingDataView::getBuildingName(BuildingType bType) const
{
    return buildings->getBuildingName(bType);
}

std::string BuildingDataView::getBuildingDescription(BuildingType bType) const
{
    return buildings->getBuildingDescription(bType);
}

unsigned BuildingDataView::getBuildingQuantity(BuildingType bType) const
{
    return buildings->getCurrentQuantity(bType);
}

std::vector<std::pair<RessourceType, double>> BuildingDataView::
    getBuildingProduction(BuildingType bType) const
{
    return buildings->getProduction(bType);
}

std::vector<std::pair<RessourceType, double>> BuildingDataView::getNextBuyCost(
    BuildingType bType) const
{
    return buildings->nextBuyCost(bType);
}

std::span<const BuildingType> BuildingDataView::getBuildingTypes() const
{
    return buildings->getBuildingTypes();
}

std::span<const BuildingType> BuildingDataView::getConversionBuildingTypes()
    const
{
    return buildings->getConversionBuildingTypes();
}

std::span<const std::pair<RessourceType, double>> BuildingDataView::
    getIncreasedStorage(BuildingType bType) const
{
    return buildings->getIncreasedStorage(bType);
}
