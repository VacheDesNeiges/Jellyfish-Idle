#include "SandNest.hpp"
#include "Ressource.hpp"
#include <cmath>
#include <fmt/core.h>
#include <utility>

SandNest::SandNest ()
{
  basePrice.push_back (std::make_pair (RessourceType::Sand, 10));
  priceMultiplier = 2;
  name = "Sand Nest";
}

std::list<std::pair<RessourceType, double> >
SandNest::getProdPerTick ()
{
  return prodPerTick;
}

void
SandNest::update ()
{
  return;
}
