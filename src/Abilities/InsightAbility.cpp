#include "InsightAbility.hpp"
#include "GameIDsTypes.hpp"

#include <iostream>

InsightAbility::InsightAbility (const nlohmann::json &data)
{
  try
    {
      name = data.at ("Name");
      description = data.at ("Description");

      castingCost.reserve (data.at ("Cost").size ());

      for (const auto &cost : data.at ("Cost"))
        {
          castingCost.push_back ({ RessourceType (cost.at ("RessourceID")),
                                   cost.at ("Quantity") });
        }

      for (const auto &effect : data.at ("Effect"))
        {
          baseRessourcesGained.push_back (
              { RessourceType (effect.at ("RessourceID")),
                effect.at ("Quantity") });
        }
    }
  catch (nlohmann::json::exception &e)
    {
      std::cerr << "Error while parsing an ability :\n" << e.what () << "\n";
      abort ();
    }
}

std::vector<std::pair<RessourceType, double> >
InsightAbility::getCost () const
{
  return castingCost;
}

std::vector<std::pair<RessourceType, double> >
InsightAbility::getProduction () const
{
  auto ret = baseRessourcesGained;
  for (auto &[rType, quant] : ret)
    {
      quant *= multipliersView ()->getProductionMultiplier (rType);
    }
  return ret;
}

std::string
InsightAbility::getName () const
{
  return name;
}

std::string
InsightAbility::getDescription () const
{
  return description;
}