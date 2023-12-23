#pragma once
#include "Upgrade.hpp"

class UpgradeFactory
{
public:
  static Upgrade createUpgrade (UpgradeID);
};