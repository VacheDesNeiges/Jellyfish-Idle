#include "BuildingManager.hpp"

#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

BuildingManager::BuildingManager()
{
    auto fstream = FilePaths::getFileStream(FilePaths::BuildingsPath);

    try
    {
        auto buildingsJson = nlohmann::json::parse(fstream);

        buildings.reserve(buildingsJson["Buildings"].size());
        buildingTypes.reserve(buildingsJson["Buildings"].size());

        for (const auto &building : buildingsJson["Buildings"])
        {
            buildings.try_emplace(BuildingType(building["BuildingID"]),
                                  building);

            buildingTypes.emplace_back(building["BuildingID"]);

            if (building.contains("Conversion"))
            {
                conversionBuildingsTypes.emplace_back(building["BuildingID"]);
            }
        }
    }

    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing buildings :\n" << e.what() << "\n";
        abort();
    }
}

void BuildingManager::buy(BuildingType bType)
{
    buildings[bType].buy();
}

unsigned BuildingManager::getCurrentQuantity(BuildingType bType) const
{
    return buildings.at(bType).getCurrentQuantity();
}

std::vector<std::pair<RessourceType, double>> BuildingManager::getProduction(
    BuildingType bType) const
{
    auto result = buildings.at(bType).getProdPerTick();
    for (auto &[rType, prod] : result)
    {
        prod *= multipliersView()->getProductionMultiplier(bType);
    }
    return result;
}

std::vector<std::pair<RessourceType, double>> BuildingManager::getConsumption(
    BuildingType bType) const
{
    return buildings.at(bType).getConsumPerTick();
}

std::vector<std::pair<RessourceType, double>> BuildingManager::nextBuyCost(
    BuildingType bType) const
{
    return buildings.at(bType).getNextBuyCost();
}

std::string BuildingManager::getBuildingName(BuildingType bType) const
{
    return buildings.at(bType).getBuildingName();
}

std::string BuildingManager::getBuildingDescription(BuildingType bType) const
{
    return buildings.at(bType).getDescription();
}

std::unordered_map<RessourceType, double> BuildingManager::getProductionRates()
    const
{
    std::unordered_map<RessourceType, double> result;
    for (const auto &[bType, b] : buildings)
    {
        if (std::ranges::find(conversionBuildingsTypes, bType) !=
            conversionBuildingsTypes.end())
            continue;

        for (const auto &[rType, productionRate] : b.getProdPerTick())
        {
            result[rType] +=
                (productionRate *
                 multipliersView()->getProductionMultiplier(bType));
        }
    }
    return result;
}

std::unordered_map<RessourceType, double> BuildingManager::getConsumptionRates()
    const
{
    std::unordered_map<RessourceType, double> result;
    for (const auto &[bType, b] : buildings)
    {
        if (std::ranges::find(conversionBuildingsTypes, bType) !=
            conversionBuildingsTypes.end())
            continue;

        for (const auto &[rType, consumptionRate] : b.getConsumPerTick())
        {
            result[rType] += consumptionRate;
        }
    }
    return result;
}

bool BuildingManager::doesIncreasesMaxJellies(BuildingType bType) const
{
    return buildings.at(bType).getIncreaseToMaxJfish() > 0;
}

unsigned BuildingManager::getIncreaseToMaxJfish(BuildingType bType)
{
    return buildings[bType].getIncreaseToMaxJfish() *
           buildings[bType].getCurrentQuantity();
}

std::vector<std::pair<BuildingType, unsigned>> BuildingManager::getData() const
{
    std::vector<std::pair<BuildingType, unsigned>> result;
    result.reserve(buildings.size());
    for (const auto &[type, building] : buildings)
    {
        result.emplace_back(type, building.getCurrentQuantity());
    }

    return result;
}

void BuildingManager::loadData(
    const std::vector<std::pair<BuildingType, unsigned>> &data)
{
    for (const auto &[type, quant] : data)
    {
        buildings[type].setQuantity(quant);
        buildings[type].update();
    }
}

std::span<const BuildingType> BuildingManager::getBuildingTypes() const
{
    return std::span(buildingTypes);
}

std::span<const BuildingType> BuildingManager::getConversionBuildingTypes()
    const
{
    return std::span(conversionBuildingsTypes);
}

bool BuildingManager::doesIncreasesRessourcesMaxQuantities(
    BuildingType bType) const
{
    return !buildings.at(bType).getIncreasedStorage().empty();
}

std::span<const std::pair<RessourceType, double>> BuildingManager::
    getIncreasedStorage(BuildingType bType) const
{
    return buildings.at(bType).getIncreasedStorage();
}
