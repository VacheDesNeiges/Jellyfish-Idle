#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <span>
#include <utility>

class RessourceManager;

class RessourceDataView
{
public:
  explicit RessourceDataView (std::shared_ptr<RessourceManager>);

  bool
  canAfford (const std::vector<std::pair<RessourceType, double> > &) const;
  double getRessourceQuantity (RessourceType) const;
  double getRessourceMaxQuantity (RessourceType) const;
  std::string_view getRessourceName (RessourceType) const;
  double getRessourceProduction (RessourceType) const;
  double getRessourceConsumption (RessourceType) const;

  std::span<const RessourceType> getRegularRessourceTypes () const;
  std::span<const RessourceType> getRareRessourceTypes () const;
  std::span<const RessourceType> getCraftableRessourceTypes () const;

private:
  std::shared_ptr<const RessourceManager> ressources;
};