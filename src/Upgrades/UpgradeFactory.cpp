#include "UpgradeFactory.hpp"
#include "Upgrade.hpp"
#include "UpgradeId.hpp"

Upgrade
UpgradeFactory::createUpgrade (UpgradeID id)
{
  std::string name;
  std::string description;
  switch (id)
    {

    case UpgradeID::FocusingForInsight:
      name = "Focus";
      description = "Description for focusing";
      break;

    case UpgradeID::Writing:
      name = "Writing";
      description = "Description for writing";
      break;

    case UpgradeID::Manufacturing:
      name = "Manufacturing";
      description = "Description for manufacturing";
      break;
    default:
      break;
    }
  return Upgrade (name, description);
}