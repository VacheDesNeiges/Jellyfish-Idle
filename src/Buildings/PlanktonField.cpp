#include "PlanktonField.hpp"
#include "Ressource.hpp"

#include <cmath>
#include <fmt/core.h>
#include <string>
#include <utility>

PlanktonField::PlanktonField ()
{
  prodPerTick.emplace_back (RessourceType::Food, 0);
  basePrice.emplace_back (RessourceType::Food, 5);
  priceMultiplier = 1.20;
  name = "Plankton Field";
}

std::list<std::pair<RessourceType, double> >
PlanktonField::getProdPerTick ()
{
  return prodPerTick;
}

void
PlanktonField::update ()
{
  for (auto &[ressource, production] : prodPerTick)
    {
      if (ressource == RessourceType::Food)
        production = baseFoodProduction * quantity;
    }
}
