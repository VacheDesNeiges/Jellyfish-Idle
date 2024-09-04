#include "AbilityManager.hpp"

#include "FilePaths.hpp"
#include "GameIDsTypes.hpp"
#include <cstdio>
#include <iostream>
#include <span>

AbilityManager::AbilityManager()
{
    auto fstream = FilePaths::getFileStream(FilePaths::AbilitiesPath);

    try
    {
        auto abilitiesJson = nlohmann::json::parse(fstream);
        abilities.reserve(abilitiesJson.at("Ability").size());
        abilitiesTypes.reserve(abilitiesJson.at("Ability").size());

        for (const auto &ability : abilitiesJson["Ability"])
        {
            abilities.try_emplace(AbilityType(ability.at("ID")), ability);
            abilitiesTypes.emplace_back(ability.at("ID"));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing abilities :\n" << e.what() << "\n";
        abort();
    }
}

bool AbilityManager::isUsable(AbilityType abiType) const
{
    bool buyable = true;
    for (const auto &[ressource, cost] : abilities.at(abiType).getCost())
    {

        if (!buyable)
            continue;

        if (ressourcesView()->getRessourceQuantity(ressource) < cost)
        {
            buyable = false;
        }
    }
    return buyable;
}

std::vector<std::pair<RessourceType, double>> AbilityManager::getAbilityCost(
    AbilityType abiType) const
{
    return abilities.at(abiType).getCost();
}

std::vector<std::pair<RessourceType, double>> AbilityManager::getProduction(
    AbilityType abiType) const
{
    return abilities.at(abiType).getProduction();
}

std::string AbilityManager::getAbilityName(AbilityType abiType) const
{
    return abilities.at(abiType).getName();
}

std::string AbilityManager::getAbilityDescription(AbilityType abiType) const
{
    return abilities.at(abiType).getDescription();
}

std::span<const AbilityType> AbilityManager::getAllAbilityTypes() const
{
    return abilitiesTypes;
}
