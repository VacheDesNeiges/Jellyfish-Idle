#include "SandNest.hpp"
#include "Ressource.hpp"
#include <cmath>
#include <fmt/core.h>
#include <utility>

SandNest::SandNest ()
{
  basePrice.emplace_back (RessourceType::Sand, 10);
  priceMultiplier = 2;
  name = "Sand Nest";
  increaseToMaxJfish = 1;
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
