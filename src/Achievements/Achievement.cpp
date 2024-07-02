#include "Achievement.hpp"
#include <algorithm>

bool
Achievement::isUnlocked () const
{
  return unlocked;
}

void
Achievement::unlock ()
{
  unlocked = true;
}

void
Achievement::setState (bool b)
{
  unlocked = b;
}

bool
Achievement::ressourcesConditionsMet () const
{
  return std::ranges::none_of (ressourceCondition, [this] (const auto &pair) {
    const auto &[rType, requirement] = pair;
    return ressourcesView ()->getRessourceQuantity (rType) <= requirement;
  });
}

bool
Achievement::buildingConditionsMet () const
{
  return std::ranges::none_of (buildingsCondition, [this] (const auto &pair) {
    const auto &[bType, requirement] = pair;
    return buildingsView ()->getBuildingQuantity (bType) < requirement;
  });
}

bool
Achievement::unlockConditionMet () const
{

  if (jelliesView ()->getNumJellies () < jfishNumCondition)
    return false;

  if (!ressourcesConditionsMet ())
    return false;

  if (!buildingConditionsMet ())
    return false;

  return true;
}