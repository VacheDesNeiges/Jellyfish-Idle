#include "Upgrade.hpp"
#include "GameIDsTypes.hpp"
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string_view>

Upgrade::Upgrade (const nlohmann::json &json)
{

  try
    {
      name = json.at ("Name");
      description = json.at ("Description");
      for (const auto &price : json.at ("Cost"))
        {
          cost.push_back ({ RessourceType (price.at ("RessourceID")),
                            price.at ("Quantity") });
        }

      if (json.contains ("UpgradeDependencyID"))
        {
          dependency = UpgradeID (json.at ("UpgradeDependencyID"));
        }
      else
        {
          dependency = std::nullopt;
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing an upgrade :\n" << e.what () << "\n";
      abort ();
    }
}

void
Upgrade::unlock ()
{
  bought = true;
}

bool
Upgrade::isUnlocked () const
{
  return bought;
}

std::string_view
Upgrade::getName () const
{
  return name;
}

std::string_view
Upgrade::getDescription () const
{
  return description;
}

std::vector<std::pair<RessourceType, double> >
Upgrade::getCost () const
{
  return cost;
}