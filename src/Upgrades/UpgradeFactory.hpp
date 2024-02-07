#pragma once
#include "Upgrade.hpp"
#include "UpgradeId.hpp"

class UpgradeFactory
{
public:
  static Upgrade createUpgrade (UpgradeID);
};