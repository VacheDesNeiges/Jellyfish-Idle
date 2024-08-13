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
            abilitiesTypes.push_back(AbilityType(ability.at("ID")));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing abilities :\n" << e.what() << "\n";
        abort();
    }
}

bool AbilityManager::isUsable(AbilityType t) const
{
    bool buyable = true;
    for (const auto &[ressource, cost] : abilities.at(t).getCost())
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
    AbilityType t) const
{
    return abilities.at(t).getCost();
}

std::vector<std::pair<RessourceType, double>> AbilityManager::getProduction(
    AbilityType t) const
{
    return abilities.at(t).getProduction();
}

std::string AbilityManager::getAbilityName(AbilityType t) const
{
    return abilities.at(t).getName();
}

std::string AbilityManager::getAbilityDescription(AbilityType t) const
{
    return abilities.at(t).getDescription();
}

std::span<const AbilityType> AbilityManager::getAllAbilityTypes() const
{
    return std::span(abilitiesTypes);
}