#pragma once

#include "Building.hpp"
#include <vector>

class SaveSystem
{
public:
  static void save (const std::vector<std::pair<BuildingType, unsigned> > &);
  static void loadFromFile ();
};