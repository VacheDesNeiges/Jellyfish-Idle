#pragma once
#include "Building.hpp"
#include "Ressource.hpp"
#include <list>
class SandNest : public Building
{
public:
  explicit SandNest ();
  std::list<std::pair<RessourceType, double> > getProdPerTick () override;
  void update () override;
};