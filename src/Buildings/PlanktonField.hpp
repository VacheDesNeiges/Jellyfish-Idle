#include "Building.hpp"
#include <iostream>

class PlanktonField : public Building
{
public:
  explicit PlanktonField ();
  ~PlanktonField () override = default;

  std::list<std::pair<RessourceType, double> > getProdPerTick () override;

  void update () override;
  std::string getDescription () override;

private:
  const double baseFoodProduction = 0.125;
};