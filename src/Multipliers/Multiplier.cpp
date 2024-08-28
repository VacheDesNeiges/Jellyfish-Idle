#include "Multiplier.hpp"
#include "GameIDsTypes.hpp"

Multiplier::Multiplier(double baseMult) : baseMultiplier(baseMult)
{
}

double Multiplier::getBaseMultiplier() const
{
    return baseMultiplier;
}

PerBuildingMultiplier::PerBuildingMultiplier(double baseMult,
                                             BuildingType buildingType)
    : Multiplier(baseMult), bType(buildingType)
{
}

double PerBuildingMultiplier::getMultValue() const
{
    return getBaseMultiplier() * buildingsView()->getBuildingQuantity(bType);
}

PerRessourceMultiplier::PerRessourceMultiplier(double baseMult,
                                               RessourceType ressourceType)
    : Multiplier(baseMult), rType(ressourceType)
{
}

double PerRessourceMultiplier::getMultValue() const
{
    return getBaseMultiplier() * ressourcesView()->getRessourceQuantity(rType);
}
