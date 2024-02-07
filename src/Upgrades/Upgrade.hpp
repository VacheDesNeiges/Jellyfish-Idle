#pragma once
#include "Ressource.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Upgrade
{
public:
  Upgrade () = default;
  Upgrade (const std::string &name, const std::string &desc,
           const std::vector<std::pair<RessourceType, double> > &cost);
  bool isUnlocked () const;
  void unlock ();
  std::string_view getName () const;
  std::string_view getDescription () const;
  std::vector<std::pair<RessourceType, double> > getCost () const;

private:
  bool bought = false;
  const std::string name;
  const std::string description;
  std::vector<std::pair<RessourceType, double> > cost;
};
