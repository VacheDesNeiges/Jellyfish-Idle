#include "UpgradeFactory.hpp"

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
      cost.emplace_back (std::pair{ RessourceType::Food, 300 });
      break;

    case UpgradeID::Telekinesis:
      name = "Telekinesis";
      description
          = "The octopus teaches you how to use insight to move heavy objects."
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
        cost.emplace_back (std::pair{ RessourceType::Insight, 100 });
        break;
      }
    case UpgradeID::Leveling:
      {
        name = "Long Term Memory";
        description = "Enhances your knowledge of things over time, making "
                      "your jellyfishs more effective";
        cost.emplace_back (std::pair{ RessourceType::KnowledgeTablet, 50 });
        break;
      }
    }
  return Upgrade (name, description, cost);
}