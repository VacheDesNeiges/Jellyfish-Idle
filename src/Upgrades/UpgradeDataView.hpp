#pragma once
#include "GameDataView.hpp"
#include "Ressource.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include <memory>

class UpgradeDataView
{
public:
  explicit UpgradeDataView (std::shared_ptr<UpgradeManager>,
                            std::shared_ptr<RessourceManager>);

  bool isBuyable (UpgradeID) const;
  bool isBought (UpgradeID) const;
  std::string_view getName (UpgradeID) const;
  std::string_view getDescription (UpgradeID) const;
  std::list<std::pair<RessourceType, double> > getCost (UpgradeID) const;

private:
  std::shared_ptr<UpgradeManager> upgrades;
  std::shared_ptr<RessourceManager> ressources;
};