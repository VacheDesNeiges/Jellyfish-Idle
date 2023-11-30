#include "GameDataSynchronizer.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "DepthSystem.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "SaveSystem.hpp"
#include <string>

GameDataSynchronizer::GameDataSynchronizer ()
{
  using enum AchievementIDs;
  achievementConditions = {
    { PlanktonField,
      [this] () {
        return ressources.getCurrentQuantity (RessourceType::Food) >= 5;
      } },

    { FirstSandNest,
      [this] () {
        return ressources.getCurrentQuantity (RessourceType::Sand) >= 1;
      } },

    { FirstJelly, [this] () { return jellies.getNumJellies () >= 1; } },

    { JobFocusing,
      [this] () {
        return buildings.getCurrentQuantity (BuildingType::SandNest) >= 1;
      } },

    { JobExploreTheDepths,
      [this] () { return jellies.getNumJellies () >= 1; } },

    { FirstInsightAbility,
      [this] () {
        return ressources.getCurrentQuantity (RessourceType::Insight) >= 1;
      } },

    { ResearchTabUnlocked, [] () { return false; } },
    { ReachedDepth100, [this] () { return depth.getCurrentDepth () >= 100; } }
  };
}

void
GameDataSynchronizer::gameTick ()
{
  ressources.zerosValuePerTick ();
  // Ressource consumption
  ressources.consume (jellies.getConsumptionRates ());
  // Ressource conversion
  // Ressource production
  ressources.produce (addMaps (buildings.getProductionRates (),
                               jellies.getProductionRates ()));

  depth.ExploreDepth (jellies.getNum (JellyJobs::ExploreTheDepths));

  checkAchievements ();
  checkJellyfishArrival ();
}

void
GameDataSynchronizer::gatherFood ()
{
  ressources.gatherFood ();
}

double
GameDataSynchronizer::getRessourceQuantity (RessourceType t)
{
  return ressources.getCurrentQuantity (t);
}

double
GameDataSynchronizer::getRessourceMaxQuantity (RessourceType t)
{
  return ressources.getMaxQuantity (t);
}

void
GameDataSynchronizer::buy (BuildingType t)
{
  for (const auto &[rType, quant] : buildings.nextBuyCost (t))
    {
      ressources.add (rType, -quant);
    }
  buildings.buy (t);

  if (buildings.doesIncreasesMaxJellies (t))
    updateMaxNumJellies ();
}

unsigned
GameDataSynchronizer::getBuildingQuantity (BuildingType t)
{
  return buildings.getCurrentQuantity (t);
}

std::list<std::pair<RessourceType, double> >
GameDataSynchronizer::getBuildingProduction (BuildingType t)
{
  return buildings.getProduction (t);
}

unsigned long
GameDataSynchronizer::getNumJellies () const
{
  return jellies.getNumJellies ();
}

long
GameDataSynchronizer::getNumJellies (JellyJobs j)
{
  return jellies.getNum (j);
}

unsigned long
GameDataSynchronizer::getMaxNumJellies () const
{
  return jellies.getMaxNumJellies ();
}

bool
GameDataSynchronizer::assignJelly (JellyJobs j)
{
  return jellies.assign (j);
}

bool
GameDataSynchronizer::unassignJelly (JellyJobs j)
{
  return jellies.unasign (j);
}

std::string_view
GameDataSynchronizer::getRessourceName (RessourceType r)
{
  return ressources.getName (r);
}

bool
GameDataSynchronizer::isUnlocked (AchievementIDs id)
{
  return achievements.isUnlocked (id);
}

bool
GameDataSynchronizer::isUnlocked (BuildingType t)
{
  using enum BuildingType;
  switch (t)
    {
    case PlanktonField:
      return achievements.isUnlocked (AchievementIDs::PlanktonField);

    case SandNest:
      return achievements.isUnlocked (AchievementIDs::FirstSandNest);

    default:
      return false;
    }
}

bool
GameDataSynchronizer::isUnlocked (JellyJobs j)
{
  using enum JellyJobs;
  switch (j)
    {
    case GatherSand:
      return achievements.isUnlocked (AchievementIDs::FirstJelly);

    case ExploreTheDepths:
      return achievements.isUnlocked (AchievementIDs::JobExploreTheDepths);

    case FocusForInsight:
      return achievements.isUnlocked (AchievementIDs::JobFocusing);

    default:
      return false;
    }
}

bool
GameDataSynchronizer::isUnlocked (RessourceType r)
{
  using enum RessourceType;

  switch (r)
    {
    case Food:
      return true;

    case Sand:
      return achievements.isUnlocked (AchievementIDs::FirstJelly);

    case Insight:
      return achievements.isUnlocked (AchievementIDs::JobFocusing);

    case Glass:
      return achievements.isUnlocked (AchievementIDs::FirstInsightAbility);

    default:
      return false;
    }
}

bool
GameDataSynchronizer::isUnlocked (AbilityType t)
{
  using enum AbilityType;
  switch (t)
    {
    case CallThunder:
      return achievements.isUnlocked (AchievementIDs::FirstInsightAbility);
    }
}

void
GameDataSynchronizer::unlock (AchievementIDs id)
{
  achievements.unlock (id);
}

void
GameDataSynchronizer::checkAchievements ()
{
  using enum AchievementIDs;
  for (auto a = static_cast<int> (PlanktonField); a != static_cast<int> (Last);
       a++)
    {
      auto id = static_cast<AchievementIDs> (a);
      using enum AchievementIDs;
      if (achievements.isUnlocked (id))
        continue;

      if (achievementConditions[id]())
        achievements.unlock (id);
    }
}

void
GameDataSynchronizer::checkJellyfishArrival ()
{
  static short gameTicksInterval = 0;
  if (jellies.getNumJellies () == jellies.getMaxNumJellies ())
    {
      gameTicksInterval = 0;
    }
  else
    {
      gameTicksInterval++;
      if (gameTicksInterval == 8
          && ressources.getNetProduction (RessourceType::Food) >= 0.5)
        // TODO refactor this 0.5 value to use the consumption rate of a
        // singular jelly instead
        {
          gameTicksInterval = 0;
          jellies.createJellyfish ();
        }
      if (gameTicksInterval >= 8)
        gameTicksInterval = 0;
    }
}

bool
GameDataSynchronizer::isBuyable (BuildingType t)
{
  bool buyable = true;
  for (const auto &[ressource, price] : buildings.nextBuyCost (t))
    {
      if (price > ressources.getCurrentQuantity (ressource))
        buyable = false;
    }
  return buyable;
}

std::string
GameDataSynchronizer::getBuildingName (BuildingType t)
{
  return buildings.getBuildingName (t);
}

std::string
GameDataSynchronizer::getBuildingDescription (BuildingType t)
{
  return buildings.getDescription (t);
}

std::string
GameDataSynchronizer::getAdvancedBuildingDescription (BuildingType t)
{
  return buildings.getAdvancedDescription (t);
}

std::map<RessourceType, double>
GameDataSynchronizer::addMaps (
    const std::map<RessourceType, double> &map1,
    const std::map<RessourceType, double> &map2) const
{
  auto result = map1;

  for (const auto &[key, value] : map2)
    {
      result[key] += value;
    }
  return result;
}

void
GameDataSynchronizer::updateMaxNumJellies ()
{
  using enum BuildingType;
  unsigned n = 0;
  for (const auto &b : Building::BuildingTypes)
    {
      n += buildings.getIncreaseToMaxJfish (b);
    }
  jellies.setBonusMaxJellies (n);
}

std::string
GameDataSynchronizer::getJobDescription (JellyJobs j) const
{
  return jellies.getJobDescription (j);
}

std::string
GameDataSynchronizer::getAbilityName (AbilityType t)
{
  return abilities.getAbilityName (t);
}

std::string
GameDataSynchronizer::getAbilityDescription (AbilityType t)
{
  return abilities.getAbilityDescription (t);
}

void
GameDataSynchronizer::save () const
{
  SaveSystem::save (buildings.getData (), achievements.getData (),
                    ressources.getData (), jellies.getData ());
  // TODO : refactor to use a SaveData object instead ?
}

void
GameDataSynchronizer::loadSave ()
{
  auto loadedData = SaveSystem::loadFromFile ();
  buildings.loadData (loadedData.buildings);
  achievements.loadData (loadedData.achievements);
  ressources.loadData (loadedData.ressources);
  jellies.loadData (loadedData.jellies);
  updateMaxNumJellies ();
}

bool
GameDataSynchronizer::isUsable (AbilityType t)
{
  bool result = true;
  for (const auto &[rType, quant] : abilities.getAbilityCost (t))
    {
      if (ressources.getCurrentQuantity (rType) < quant)
        result = false;
    }

  return result;
}

void
GameDataSynchronizer::useAbility (AbilityType t)
{
  if (isUsable (t))
    {

      for (const auto &[rType, quant] : abilities.getAbilityCost (t))
        {
          ressources.add (rType, -quant);
        }

      for (const auto &[rType, quant] : abilities.getProduction (t))
        {
          ressources.add (rType, quant);
        }
    }
}

double
GameDataSynchronizer::getRessourceProduction (RessourceType r)
{
  return ressources.getProduction (r);
}

double
GameDataSynchronizer::getRessourceConsumption (RessourceType r)
{
  return ressources.getConsumption (r);
}

unsigned
GameDataSynchronizer::getCurrentDepth () const
{
  return depth.getCurrentDepth ();
}

float
GameDataSynchronizer::getDepthProgress () const
{
  return depth.getCurrentProgress ()
         / depth.getProgressNeededForNextIncrease ();
}