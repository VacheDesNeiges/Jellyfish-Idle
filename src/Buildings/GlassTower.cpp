#include "GlassTower.hpp"
#include "Ressource.hpp"
#include <list>

GlassTower::GlassTower ()
{
  basePrice.push_back ({ RessourceType::Glass, 15 });
  priceMultiplier = 1.30;
  name = "Glass Tower";
}

std::list<std::pair<RessourceType, double> >
GlassTower::getProdPerTick ()
{
  return prodPerTick;
}

void
GlassTower::update ()
{
  for (auto &[ressource, production] : prodPerTick)
    {
      if (ressource == RessourceType::Food)
        production = baseProduction * quantity;
    }
}