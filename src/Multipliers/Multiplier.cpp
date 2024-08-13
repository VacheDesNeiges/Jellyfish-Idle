#include "Multiplier.hpp"
#include "GameIDsTypes.hpp"

Multiplier::Multiplier(double baseMult) : baseMultiplier(baseMult)
{
}

PerBuildingMultiplier::PerBuildingMultiplier(double baseMult, BuildingType b)
    : Multiplier(baseMult), bType(b)
{
}

double PerBuildingMultiplier::getMultValue() const
{
    return baseMultiplier * buildingsView()->getBuildingQuantity(bType);
}

PerRessourceMultiplier::PerRessourceMultiplier(double baseMult, RessourceType r)
    : Multiplier(baseMult), rType(r)
{
}

double PerRessourceMultiplier::getMultValue() const
{
    return baseMultiplier * ressourcesView()->getRessourceQuantity(rType);
}