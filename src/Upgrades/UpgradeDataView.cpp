#include "UpgradeDataView.hpp"
#include "GameDataView.hpp"
#include "Ressource.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include <memory>
#include <new>

UpgradeDataView::UpgradeDataView (std::shared_ptr<UpgradeManager> u,
                                  std::shared_ptr<RessourceManager> r)
    : upgrades (u), ressources (r)
{
}

bool
UpgradeDataView::isBuyable (UpgradeID id) const
{
  return false; // FIXME;
}

std::string_view
UpgradeDataView::getName (UpgradeID id) const
{
  return upgrades->getName (id);
}

std::string_view
UpgradeDataView::getDescription (UpgradeID id) const
{
  return upgrades->getDescription (id);
}

std::list<std::pair<RessourceType, double> >
UpgradeDataView::getCost (UpgradeID id) const
{
  return upgrades->getCost (id);
}