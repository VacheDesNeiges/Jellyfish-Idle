#include "AquaCulture.hpp"
#include "GameIDsTypes.hpp"
#include <cassert>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

AquaCulture::AquaCulture(const nlohmann::json &json)
{
    try
    {
        name = json.at("Name");

        if (json.contains("Production"))
        {
            for (const auto &prod : json.at("Production"))
            {
                baseProduction.emplace_back(
                    RessourceType(prod.at("RessourceID")), prod.at("Quantity"));
            }
        }

        if (json.contains("Consumption"))
        {
            for (const auto &cons : json.at("Consumption"))
            {
                baseConsumption.emplace_back(
                    RessourceType(cons.at("RessourceID")), cons.at("Quantity"));
            }
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing a culture :\n" << e.what() << "\n";
        abort();
    }
}

void AquaCulture::start()
{
    cultureOngoing = true;
}

void AquaCulture::cancel()
{
    cultureOngoing = false;
}

bool AquaCulture::isOngoing() const
{
    return cultureOngoing;
}

CultureData AquaCulture::getData() const
{
    CultureData result{
        result.craftOngoing = cultureOngoing,
        result.fieldCount = 0,
    };
    return result;
}

void AquaCulture::loadData(const CultureData &data)
{
    cultureOngoing = data.craftOngoing;
}

std::vector<std::pair<RessourceType, double>> AquaCulture::getBaseConsumption()
    const
{
    return baseConsumption;
}

std::vector<std::pair<RessourceType, double>> AquaCulture::getBaseProduction()
    const
{
    return baseProduction;
}

std::string AquaCulture::getName() const
{
    return name;
}