#include "RessourceDataView.hpp"
#include "GameIDsTypes.hpp"
#include "RessourceManager.hpp"
#include <utility>
#include <vector>

RessourceDataView::RessourceDataView(
    const std::shared_ptr<RessourceManager> &rManager)
    : ressources(rManager)
{
}

double RessourceDataView::getRessourceProduction(RessourceType rType) const
{
    return ressources->getProduction(rType);
}

double RessourceDataView::getRessourceConsumption(RessourceType rType) const
{
    return ressources->getConsumption(rType);
}

std::string_view RessourceDataView::getRessourceName(RessourceType rType) const
{
    return ressources->getName(rType);
}

double RessourceDataView::getRessourceQuantity(RessourceType rType) const
{
    return ressources->getCurrentQuantity(rType);
}

double RessourceDataView::getRessourceMaxQuantity(RessourceType rType) const
{
    return ressources->getMaxQuantity(rType);
}

std::span<const RessourceType> RessourceDataView::getRegularRessourceTypes()
    const
{
    return ressources->getRegularRessourceTypes();
}

std::span<const RessourceType> RessourceDataView::getRareRessourceTypes() const
{
    return ressources->getRareRessourceTypes();
}
std::span<const RessourceType> RessourceDataView::getCraftableRessourceTypes()
    const
{
    return ressources->getCraftableRessourceTypes();
}

bool RessourceDataView::canAfford(
    const std::vector<std::pair<RessourceType, double>> &vector) const
{
    return ressources->canAfford(vector);
}
