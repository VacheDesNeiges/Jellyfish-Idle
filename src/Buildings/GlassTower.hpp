#include "Building.hpp"

class GlassTower : public Building
{
public:
  explicit GlassTower ();
  ~GlassTower () override = default;

  std::list<std::pair<RessourceType, double> > getProdPerTick () override;

  void update () override;

private:
  const double baseProduction = 0.20;
};