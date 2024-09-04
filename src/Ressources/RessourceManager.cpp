#include "RessourceManager.hpp"
#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <utility>
#include <vector>

RessourceManager::RessourceManager()
{
    init();
}

void RessourceManager::init()
{
    auto fstream = FilePaths::getFileStream(FilePaths::RessourcesPath);

    try
    {
        nlohmann::json ressourcesJson = nlohmann::json::parse(fstream);

        ressources.reserve(ressourcesJson.at("Ressources").size() +
                           ressourcesJson.at("RareRessources").size() +
                           ressourcesJson.at("ManufacturedRessources").size());

        regularRessourceTypes.reserve(ressourcesJson.at("Ressources").size());
        for (const auto &resData : ressourcesJson["Ressources"])
        {
            ressources.try_emplace(RessourceType(resData.at("Id")), resData);
            regularRessourceTypes.emplace_back(resData.at("Id"));
        }

        rareRessourceTypes.reserve(ressourcesJson["RareRessources"].size());
        for (const auto &resData : ressourcesJson["RareRessources"])
        {
            ressources.try_emplace(RessourceType(resData.at("Id")), resData);
            rareRessourceTypes.emplace_back(resData.at("Id"));
        }

        craftableRessourceTypes.reserve(
            ressourcesJson["ManufacturedRessources"].size());
        for (const auto &resData : ressourcesJson["ManufacturedRessources"])
        {
            ressources.try_emplace(RessourceType(resData.at("Id")), resData);

            craftableRessourceTypes.emplace_back(resData.at("Id"));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing ressources :\n" << e.what() << "\n";
        abort();
    }
    allRessourceTypes.reserve(regularRessourceTypes.size() +
                              rareRessourceTypes.size() +
                              craftableRessourceTypes.size());

    allRessourceTypes.insert(allRessourceTypes.end(),
                             regularRessourceTypes.begin(),
                             regularRessourceTypes.end());

    allRessourceTypes.insert(allRessourceTypes.end(),
                             rareRessourceTypes.begin(),
                             rareRessourceTypes.end());

    allRessourceTypes.insert(allRessourceTypes.end(),
                             craftableRessourceTypes.begin(),
                             craftableRessourceTypes.end());
}

void RessourceManager::gatherSand()
{
    ressources[RessourcesAlias::SAND].add(1);
}

double RessourceManager::getCurrentQuantity(RessourceType rType) const
{
    return ressources.at(rType).getCurrentQuantity();
}

double RessourceManager::getMaxQuantity(RessourceType rType) const
{
    return ressources.at(rType).getMaxQuantity();
}

bool RessourceManager::canAfford(
    const std::vector<std::pair<RessourceType, double>> &vector) const
{
    return std::ranges::all_of(vector, [this](const auto &pair) {
        const auto &[rType, quant] = pair;
        return ressources.at(rType).getCurrentQuantity() >= quant;
    });
}

void RessourceManager::add(RessourceType rType, double n)
{
    ressources.at(rType).add(n);
}

void RessourceManager::add(
    const std::vector<std::pair<RessourceType, double>> &vector)
{
    for (const auto &[rType, quant] : vector)
    {
        ressources.at(rType).add(quant);
    }
}

void RessourceManager::substract(
    const std::vector<std::pair<RessourceType, double>> &vector)
{
    for (const auto &[rType, quant] : vector)
    {
        ressources.at(rType).add(-quant);
    }
}

std::string_view RessourceManager::getName(RessourceType rType) const
{
    return ressources.at(rType).getName();
}

void RessourceManager::zerosValuePerTick()
{
    for (auto &[_, res] : ressources)
    {
        res.resetValuesPerTick();
    }
}

void RessourceManager::addToProdPerTick(RessourceType rType, double n)
{
    if (n < 0)
    {
        ressources[rType].addToConsumptionPerTick(-n);
    }
    else
    {
        ressources[rType].addToProdPerTick(n);
    }
}

double RessourceManager::getNetProduction(RessourceType rType) const
{
    return ressources.at(rType).getNetProduction();
}

void RessourceManager::consume(
    const std::unordered_map<RessourceType, double> &rates)
{
    for (const auto &[type, rate] : rates)
    {
        ressources[type].add(-rate);
        ressources[type].addToConsumptionPerTick(rate);
    }
}

void RessourceManager::produce(
    const std::unordered_map<RessourceType, double> &rates)
{
    for (const auto &[type, rate] : rates)
    {
        ressources[type].add(rate);
        ressources[type].addToProdPerTick(rate);
    }
}

void RessourceManager::tryConvert(
    const std::vector<std::pair<RessourceType, double>> &from,
    const std::vector<std::pair<RessourceType, double>> &to)
{
    bool canConvert = true;
    for (const auto &[rType, cons] : from)
    {
        if (cons > ressources[rType].getCurrentQuantity())
            canConvert = false;
    }

    if (!canConvert)
        return;

    for (const auto &[rType, cons] : from)
    {
        ressources[rType].add(-cons);
        ressources[rType].addToConsumptionPerTick(cons);
    }

    for (const auto &[rType, prod] : to)
    {
        ressources[rType].add(prod);
        ressources[rType].addToProdPerTick(prod);
    }
}

std::vector<std::pair<RessourceType, double>> RessourceManager::getData() const
{
    std::vector<std::pair<RessourceType, double>> result;
    result.reserve(ressources.size());
    for (const auto &[rtype, res] : ressources)
    {
        result.emplace_back(rtype, res.getCurrentQuantity());
    }

    return result;
}

void RessourceManager::loadData(
    const std::vector<std::pair<RessourceType, double>> &data)
{
    for (const auto &[rType, quant] : data)
    {
        ressources[rType].setQuantity(quant);
    }
}

double RessourceManager::getProduction(RessourceType rType) const
{
    return ressources.at(rType).getProduction();
}

double RessourceManager::getConsumption(RessourceType rType) const
{
    return ressources.at(rType).getConsumption();
}

std::span<const RessourceType> RessourceManager::getAllRessourceTypes() const
{
    return {allRessourceTypes};
}

std::span<const RessourceType> RessourceManager::getRegularRessourceTypes()
    const
{
    return {regularRessourceTypes};
}

std::span<const RessourceType> RessourceManager::getRareRessourceTypes() const
{
    return {rareRessourceTypes};
}
std::span<const RessourceType> RessourceManager::getCraftableRessourceTypes()
    const
{
    return {craftableRessourceTypes};
}

void RessourceManager::updateMaxRessourcesQuantities(
    const std::unordered_map<RessourceType, double> &newQuantities)
{
    for (const auto &[rType, quant] : newQuantities)
    {
        ressources.at(rType).setBonusMaxQuantity(quant);
    }
}

void RessourceManager::recomputeMaxQuantities()
{
    std::unordered_map<RessourceType, double> newQuantities;
    for (const auto bType : buildingsView()->getBuildingTypes())
    {
        for (const auto &[rType, quant] :
             buildingsView()->getIncreasedStorage(bType))
        {

            newQuantities[rType] += quant;
        }
    }
    updateMaxRessourcesQuantities(newQuantities);
}
