#include "PlanktonField.hpp"
#include "Ressource.hpp"
#include <cmath>
#include <utility>

PlanktonField::PlanktonField ()
{
  prodPerTick.push_back (std::make_pair (RessourceType::Food, 0));
  basePrice.push_back (std::make_pair (RessourceType::Food, 5));
  priceMultiplier = 1.20;
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

std::string
PlanktonField::getDescription ()
{
  std::string s;
  // move it to building ?
  for (const auto &[ressource, price] : basePrice)
    {
      s += "price = "
           + std::to_string (price * pow (priceMultiplier, quantity));
    }
  return s;
}