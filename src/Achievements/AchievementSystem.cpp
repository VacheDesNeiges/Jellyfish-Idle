#include "AchievementSystem.hpp"

#include "Achievement.hpp"
#include "AchievementDataView.hpp"
#include "AchievementIDs.hpp"
#include "AquaCultureID.hpp"
#include "GameIDsTypes.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Notification.hpp"
#include "UpgradeId.hpp"

#include <optional>
#include <utility>
#include <vector>

AchievementSystem::AchievementSystem ()
{
  using enum AchievementIDs;

  achievements.reserve (allAchievementsIDs.size ());
  for (const auto a : allAchievementsIDs)
    {
      achievements.try_emplace (a, Achievement ());
    }

  notifications.reserve (achievementsWithNotification.size ());
  for (const auto a : achievementsWithNotification)
    {
      notifications.try_emplace (a, Notification (a));
    }

  achievementConditions.reserve (allAchievementsIDs.size ());
  initLambdas ();
}

bool
AchievementSystem::isUnlocked (AchievementIDs id) const
{
  return achievements.at (id).isUnlocked ();
}

void
AchievementSystem::unlock (AchievementIDs id)
{
  achievements.at (id).unlock ();
}

std::vector<std::pair<AchievementIDs, bool> >
AchievementSystem::getData () const
{
  std::vector<std::pair<AchievementIDs, bool> > result;
  result.reserve (allAchievementsIDs.size ());
  for (const auto &[id, val] : achievements)
    {
      result.emplace_back (id, val.isUnlocked ());
    }
  return result;
}

void
AchievementSystem::loadData (
    const std::vector<std::pair<AchievementIDs, bool> > &data)
{
  for (const auto &[id, unlockedState] : data)
    {
      achievements[id].setState (unlockedState);
    }
}

void
AchievementSystem::checkAchievements ()
{
  using enum AchievementIDs;
  for (const auto &id : allAchievementsIDs)
    {
      using enum AchievementIDs;
      if (isUnlocked (id))
        continue;

      if (achievementConditions[id]())
        {
          unlock (id);
          pushNotification (id);
        }
    }
}

bool
AchievementSystem::isUnlocked (BuildingType t) const
{
  switch (static_cast<int> (t))
    {
      using enum AchievementIDs;
    case static_cast<int> (BuildingsAlias::AQUATICFIELD):
      return isUnlocked (BuildingAquaticField);

    case static_cast<int> (BuildingsAlias::DUNESHELTER):
      return isUnlocked (BuildingSandNest);

    case static_cast<int> (BuildingsAlias::MINES):
      return isUnlocked (BuildingMines);

    case static_cast<int> (BuildingsAlias::GLASSNESTS):
      return isUnlocked (RessourceGlass);

    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (JellyJobs j) const
{
  using enum JellyJobs;
  using enum AchievementIDs;
  switch (j)
    {
    case GatherSand:
      return isUnlocked (FirstJelly);

    case ExploreTheDepths:
      return isUnlocked (JobExploreTheDepths);

    case FocusForInsight:
      return isUnlocked (FocusingUpgradeBought);

    case Mining:
      return isUnlocked (JobMining);

    case Artisan:
      return isUnlocked (JobArtisan);

    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (RessourceType r) const
{

  switch (static_cast<int> (r))
    {
      using enum AchievementIDs;
      using namespace RessourcesAlias;

    case static_cast<int> (FOOD):
      return isUnlocked (RessourceFood);

    case static_cast<int> (SAND):
      return true;

    case static_cast<int> (STONE):
      return isUnlocked (JobMining);

    case static_cast<int> (INSIGHT):
      return isUnlocked (FocusingUpgradeBought);

    case static_cast<int> (GLASS):
      return isUnlocked (RessourceGlass);

    case static_cast<int> (STONESLAB):
      return isUnlocked (RessourceStoneSlab);

    case static_cast<int> (GLASSPANE):
      return isUnlocked (RessourceGlassPane);

    default:
      return true;
    }
}

bool
AchievementSystem::isUnlocked (AbilityType t) const
{
  using enum AbilityType;
  switch (t)
    {
    case AbilityLightning:
      return isUnlocked (AchievementIDs::LightningAbilityBuyable);
    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (UpgradeID id) const
{
  switch (id)
    {
      using enum AchievementIDs;
      using enum UpgradeID;

    case Focusing:
      return isUnlocked (AncientOctopus);

    case Telekinesis:
      return isUnlocked (FocusingUpgradeBought);

    case AdvancedTelekinesis:
      return isUnlocked (TelekinesisUpgradeBought);

    case Writing:
      return isUnlocked (AdvancedTelekinesisUpgradeBought);

    default:
      return false;
    }
}

bool
AchievementSystem::isUnlocked (AquaCultureID id) const
{
  switch (id)
    {
      using enum AquaCultureID;
      using enum AchievementIDs;

    case Plankton:
      return isUnlocked (CulturePlankton);

    case SandWorms:
      return isUnlocked (CultureSandworm);

    case Oysters:
      return isUnlocked (CultureOyster);

    default:
      return false;
    }
}

std::optional<std::string_view>
AchievementSystem::getNotification () const
{
  if (!notificationQueue.empty ())
    return notificationQueue.front ().getNotificationText ();

  return std::nullopt;
}

void
AchievementSystem::popNotification ()
{
  notificationQueue.pop ();
}

void
AchievementSystem::pushNotification (AchievementIDs id)
{
  if (const auto it = notifications.find (id); it != notifications.end ())
    notificationQueue.push (it->second);
}