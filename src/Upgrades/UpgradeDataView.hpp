#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <vector>

class UpgradeManager;
class RessourceManager;
enum class UpgradeID;

class UpgradeDataView
{
public:
  explicit UpgradeDataView (std::shared_ptr<UpgradeManager>,
                            std::shared_ptr<RessourceManager>);

  bool isAvailableForBuying (UpgradeID) const;
  bool isBuyable (UpgradeID) const;
  bool isBought (UpgradeID) const;
  std::string_view getName (UpgradeID) const;
  std::string_view getDescription (UpgradeID) const;
  std::vector<std::pair<RessourceType, double> > getCost (UpgradeID) const;

private:
  std::shared_ptr<UpgradeManager> upgrades;
  std::shared_ptr<RessourceManager> ressources;
};