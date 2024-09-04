#include "AbilityDataView.hpp"

#include "AbilityManager.hpp"
#include "GameIDsTypes.hpp"
#include "RessourceManager.hpp"
#include <memory>

AbilityDataView::AbilityDataView(
    const std::shared_ptr<AbilityManager> &aManager,
    const std::shared_ptr<RessourceManager> &rManager)
    : abilities(aManager), ressources(rManager)
{
}

bool AbilityDataView::isUsable(AbilityType abiType) const
{
    bool result = true;
    for (const auto &[rType, quant] : abilities->getAbilityCost(abiType))
    {
        if (ressources->getCurrentQuantity(rType) < quant)
            result = false;
    }

    return result;
}

std::string AbilityDataView::getAbilityName(AbilityType abiType) const
{
    return abilities->getAbilityName(abiType);
}

std::string AbilityDataView::getAbilityDescription(AbilityType abiType) const
{
    return abilities->getAbilityDescription(abiType);
}

std::vector<std::pair<RessourceType, double>> AbilityDataView::getCost(
    AbilityType abiType) const
{
    return abilities->getAbilityCost(abiType);
}

std::span<const AbilityType> AbilityDataView::getAbilityTypes() const
{
    return abilities->getAllAbilityTypes();
}
