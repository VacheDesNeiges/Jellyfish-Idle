#include "UpgradeDataView.hpp"

#include "GameIDsTypes.hpp"
#include "RessourceManager.hpp"
#include "UpgradeManager.hpp"

#include <memory>

UpgradeDataView::UpgradeDataView(std::shared_ptr<UpgradeManager> uManager,
                                 std::shared_ptr<RessourceManager> rManager)
    : upgrades(uManager), ressources(rManager)
{
}

bool UpgradeDataView::isBuyable(UpgradeID id) const
{
    if (isBought(id))
        return false;

    bool buyable = true;
    for (const auto &[ressource, price] : upgrades->getCost(id))
    {
        if (price > ressources->getCurrentQuantity(ressource))
            buyable = false;
    }
    return buyable;
}

std::string_view UpgradeDataView::getName(UpgradeID id) const
{
    return upgrades->getName(id);
}

std::string_view UpgradeDataView::getDescription(UpgradeID id) const
{
    return upgrades->getDescription(id);
}

std::vector<std::pair<RessourceType, double>> UpgradeDataView::getCost(
    UpgradeID id) const
{
    return upgrades->getCost(id);
}

bool UpgradeDataView::isBought(UpgradeID id) const
{
    return upgrades->isBought(id);
}

bool UpgradeDataView::isAvailableForBuying(UpgradeID id) const
{
    return upgrades->isAvailableForBuying(id);
}

std::span<const UpgradeID> UpgradeDataView::getUpgradesTypes() const
{
    return upgrades->getUpgradesTypes();
}
