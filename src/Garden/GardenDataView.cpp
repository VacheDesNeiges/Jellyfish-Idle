#include "GardenDataView.hpp"
#include "GameIDsTypes.hpp"
#include "GardenManager.hpp"
#include <memory>
#include <optional>

GardenDataView::GardenDataView(const std::shared_ptr<GardenManager> &gManager)
    : garden(gManager)
{
}

std::string GardenDataView::getName(AquaCultureID id) const
{
    return garden->getName(id);
}

unsigned GardenDataView::getAssignedFieldsToCulture(AquaCultureID id) const
{
    return garden->getAssignedFieldsToCulture(id);
}

bool GardenDataView::isOngoing(AquaCultureID id) const
{
    return garden->isOngoing(id);
}

std::vector<std::pair<RessourceType, double>> GardenDataView::
    getFieldConsumption(AquaCultureID id, std::optional<unsigned> nFields) const
{
    return garden->getConsumption(id, nFields);
}

std::vector<std::pair<RessourceType, double>> GardenDataView::
    getFieldProduction(AquaCultureID id, std::optional<unsigned> nFields) const
{
    return garden->getProduction(id, nFields);
}

std::span<const AquaCultureID> GardenDataView::getCultureTypes() const
{
    return garden->getCultureTypes();
}
