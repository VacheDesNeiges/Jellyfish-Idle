#include "UpgradeFactory.hpp"
#include "Upgrade.hpp"
#include "UpgradeId.hpp"
#include "fmt/core.h"
#include "fmt/format.h"

Upgrade
UpgradeFactory::createUpgrade (UpgradeID id)
{
  std::string name;
  std::string description;
  switch (id)
    {

    case UpgradeID::FocusingForInsight:
      name = "Focus";
      description = "The Octopus teaches you how to focus\n"
                    "to gather Insight. It also asks you \n"
                    "to come back to exchange it for more\n"
                    "secrets once you gather enough of it";
      break;

    case UpgradeID::Telekinesis:
      name = "Telekinesis";
      description
          = "The octopus teaches you how to use insight to move objects."
            "This will allow you to do manual labour";
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