#include "AbilityDataView.hpp"

#include "AbilityManager.hpp"
#include "InsightAbility.hpp"
#include "RessourceManager.hpp"
#include <memory>

AbilityDataView::AbilityDataView (std::shared_ptr<AbilityManager> a,
                                  std::shared_ptr<RessourceManager> r)
    : abilities (a), ressources (r)
{
}

bool
AbilityDataView::isUsable (AbilityType t) const
{
  bool result = true;
  for (const auto &[rType, quant] : abilities->getAbilityCost (t))
    {
      if (ressources->getCurrentQuantity (rType) < quant)
        result = false;
    }

  return result;
}

std::string
AbilityDataView::getAbilityName (AbilityType t) const
{
  return abilities->getAbilityName (t);
}

std::string
AbilityDataView::getAbilityDescription (AbilityType t) const
{
  return abilities->getAbilityDescription (t);
}

std::vector<std::pair<RessourceType, double> >
AbilityDataView::getCost (AbilityType t) const
{
  return abilities->getAbilityCost (t);
}