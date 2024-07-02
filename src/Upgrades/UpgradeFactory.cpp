#include "UpgradeFactory.hpp"

#include "GameIDsTypes.hpp"
#include "Upgrade.hpp"
#include "UpgradeId.hpp"

#include <utility>
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
      description
          = "The Octopus tells you that you have a hidden potential, they "
            "propose to teach you how to use it in exchange for some food.";
      cost.emplace_back (std::pair{ RessourcesAlias::FOOD, 50 });
      break;

    case UpgradeID::Telekinesis:
      name = "Telekinesis";
      description
          = "The octopus teaches you how to use insight to move heavy objects."
            "This will allow you to do basic manual labour such as mining";
      cost.emplace_back (std::pair{ RessourcesAlias::INSIGHT, 100 });
      break;

    case UpgradeID::Writing:
      name = "Writing";
      description = "Description for writing";
      cost.emplace_back (std::pair{ RessourcesAlias::INSIGHT, 300 });
      break;

    case UpgradeID::AdvancedTelekinesis:
      {
        name = "Advanced Telekinesis";
        description = "Refine your control of Telekinesis, enabling you to "
                      "manufacture more complex items";
        cost.emplace_back (std::pair{ RessourcesAlias::INSIGHT, 200 });
        break;
      }

    case UpgradeID::AbilityLightning:
      {
        name = "Lightning Ability";
        description
            = "Allows you to use your insight to call a lightning strike. "
              "Useful to rapidly melt some sand into glass";
        cost.emplace_back (std::pair{ RessourcesAlias::INSIGHT, 100 });
        break;
      }
    case UpgradeID::Leveling:
      {
        name = "Long Term Memory";
        description = "Enhances your knowledge of things over time, making "
                      "your jellyfishs more effective";
        cost.emplace_back (std::pair{ RessourcesAlias::KNOWLEDGETABLET, 50 });
        break;
      }
    }
  return Upgrade (name, description, cost);
}