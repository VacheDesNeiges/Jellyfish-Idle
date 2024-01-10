#pragma once
#include <memory>

class RessourceManager;
enum class RessourceType;

class RessourceDataView
{
public:
  explicit RessourceDataView (std::shared_ptr<RessourceManager>);

  double getRessourceQuantity (RessourceType) const;
  double getRessourceMaxQuantity (RessourceType) const;
  std::string_view getRessourceName (RessourceType) const;
  double getRessourceProduction (RessourceType) const;
  double getRessourceConsumption (RessourceType) const;

private:
  std::shared_ptr<RessourceManager> ressources;
};