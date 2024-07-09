#pragma once
#include "GameIDsTypes.hpp"
#include <memory>
#include <span>

class RessourceManager;

class RessourceDataView
{
public:
  explicit RessourceDataView (std::shared_ptr<RessourceManager>);

  double getRessourceQuantity (RessourceType) const;
  double getRessourceMaxQuantity (RessourceType) const;
  std::string_view getRessourceName (RessourceType) const;
  double getRessourceProduction (RessourceType) const;
  double getRessourceConsumption (RessourceType) const;

  std::span<const RessourceType> getRegularRessourceTypes () const;
  std::span<const RessourceType> getRareRessourceTypes () const;
  std::span<const RessourceType> getCraftableRessourceTypes () const;

private:
  std::shared_ptr<RessourceManager> ressources;
};