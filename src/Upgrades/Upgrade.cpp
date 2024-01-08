#include "Upgrade.hpp"
#include <string_view>

Upgrade::Upgrade (const std::string &n, const std::string &desc)
    : name (n), description (desc)
{
}

void
Upgrade::unlock ()
{
  bought = true;
}

bool
Upgrade::isUnlocked () const
{
  return bought;
}

std::string_view
Upgrade::getName () const
{
  return name;
}

std::string_view
Upgrade::getDescription () const
{
  return description;
}

std::vector<std::pair<RessourceType, double> >
Upgrade::getCost () const
{
  return cost;
}