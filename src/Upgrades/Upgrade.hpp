#pragma once
#include "Building.hpp"
#include "UpgradeId.hpp"
#include <array>
#include <string>
#include <string_view>

class Upgrade
{
public:
  Upgrade () = default;
  Upgrade (const std::string &name, const std::string &desc);
  bool isUnlocked () const;
  void unlock ();
  std::string_view getName () const;
  std::string_view getDescription () const;
  std::list<std::pair<RessourceType, double> > getCost () const;

private:
  bool bought = false;
  const std::string name;
  const std::string description;
  std::list<std::pair<RessourceType, double> > cost;
};
