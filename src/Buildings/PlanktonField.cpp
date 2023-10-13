#include "PlanktonField.hpp"
#include "Ressource.hpp"
#include <utility>

PlanktonField::PlanktonField ()
{
  prodPerTick.push_back (std::make_pair (RessourceType::Food, 0));
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
      switch (ressource)
        {
        case RessourceType::Food:
          production = baseFoodProduction * quantity;
          break;
        default:
          continue;
        }
    }
}