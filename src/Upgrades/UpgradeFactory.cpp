#include "UpgradeFactory.hpp"
#include "Upgrade.hpp"
#include "UpgradeId.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include <vector>

Upgrade
UpgradeFactory::createUpgrade (UpgradeID id)
{
  std::string name;
  std::string description;
  std::vector<std::pair<RessourceType, double> > cost;
  switch (id)
    {

    case UpgradeID::Focusing:
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
            "This will allow you to do basic manual labour such as mining";
      cost.emplace_back (std::pair{ RessourceType::Insight, 100 });
      break;

    case UpgradeID::Writing:
      name = "Writing";
      description = "Description for writing";
      cost.emplace_back (std::pair{ RessourceType::Insight, 300 });
      break;

    case UpgradeID::AdvancedTelekinesis:
      {
        name = "Advanced Telekinesis";
        description = "Refine your control of Telekinesis, enabling you to "
                      "manufacture more complex items";
        cost.emplace_back (std::pair{ RessourceType::Insight, 200 });
        break;
      }

    case UpgradeID::AbilityLightning:
      {
        name = "Lightning Ability";
        description
            = "Allows you to use your insight to call a lightning strike. "
              "Useful to rapidly melt some sand into glass";
        break;
      }

    default:
      break;
    }
  return Upgrade (name, description, cost);
}