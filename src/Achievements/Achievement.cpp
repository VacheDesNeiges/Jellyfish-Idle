#include "Achievement.hpp"

#include <algorithm>
#include <nlohmann/json.hpp>

Achievement::Achievement (const nlohmann::json &json)
{
  for (const auto &condition : json.at ("Condition"))
    {
      if (condition.contains ("NumJfish"))
        {
          jfishNumCondition = condition.at ("NumJfish");
          continue;
        }

      if (condition.contains ("Depth"))
        {
          depthCondition = condition.at ("Depth");
          continue;
        }

      if (condition.contains ("AchievementID"))
        {
          achievementsCondition.push_back (
              AchievementIDs (condition.at ("AchievementID")));
          continue;
        }

      if (condition.contains ("UpgradeID"))
        {
          upgradeCondition.push_back (condition.at ("UpgradeID"));
          continue;
        }

      if (condition.contains ("RessourceID"))
        {
          ressourceCondition.push_back (std::pair<RessourceType, int>{
              condition.at ("RessourceID"), condition.at ("Quantity_GT") });
          continue;
        }

      if (condition.contains ("BuildingID"))
        {
          buildingsCondition.push_back (std::pair<BuildingType, unsigned>{
              condition.at ("BuildingID"), condition.at ("MinQuantity") });
          continue;
        }

      if (condition.contains ("AnyOf"))
        {
          if (condition.at ("AnyOf") == "Rare")
            {
              anyRareRessource = true;
            }
          else if (condition.at ("AnyOf") == "Manufactured")
            {
              AnyManufacturedRessource = true;
            }
          continue;
        }
    }
}

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
Achievement::achievementConditionsMet () const
{
  return std::ranges::none_of (achievementsCondition,
                               [this] (const auto &ach) {
                                 return !achievementsView ()->isUnlocked (ach);
                               });
}

bool
Achievement::unlockConditionMet () const
{

  if (jelliesView ()->getNumJellies () < jfishNumCondition)
    return false;

  if (!ressourceCondition.empty () && !ressourcesConditionsMet ())
    return false;

  if (!buildingsCondition.empty () && !buildingConditionsMet ())
    return false;

  if (!achievementsCondition.empty () && !achievementConditionsMet ())
    return false;

  if (anyRareRessource)
    {
      return std::ranges::any_of (
          ressourcesView ()->getRareRessourceTypes (),
          [this] (const auto &rType) {
            return ressourcesView ()->getRessourceQuantity (rType) > 0;
          });
    }

  if (AnyManufacturedRessource)
    {
      return std::ranges::any_of (
          ressourcesView ()->getCraftableRessourceTypes (),
          [this] (const auto &rType) {
            return ressourcesView ()->getRessourceQuantity (rType) > 0;
          });
    }

  return true;
}