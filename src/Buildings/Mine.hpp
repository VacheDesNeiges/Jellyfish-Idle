// By using rocks, you can stop the galleries from collapsing and dig deeper !
#pragma once
#include "Building.hpp"
#include "Ressource.hpp"
#include <utility>

class Mine : public Building
{
public:
  explicit Mine ();
  std::list<std::pair<RessourceType, double> > getProdPerTick () override;
  void update () override;
};