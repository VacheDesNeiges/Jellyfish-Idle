#include "PlanktonField.hpp"
#include "Ressource.hpp"

#include <cmath>
#include <fmt/core.h>
#include <string>
#include <utility>

PlanktonField::PlanktonField ()
{
  prodPerTick.push_back (std::make_pair (RessourceType::Food, 0));
  basePrice.push_back (std::make_pair (RessourceType::Food, 5));
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
