#include "Mine.hpp"
#include "Ressource.hpp"

Mine::Mine ()
{
  basePrice.emplace_back (RessourceType::Stone, 15);
  priceMultiplier = 1.15;
  name = "Mine";
}

std::list<std::pair<RessourceType, double> >
Mine::getProdPerTick ()
{
  return prodPerTick;
}

void
Mine::update ()
{
  return;
}