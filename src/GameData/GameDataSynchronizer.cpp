#include "GameDataSynchronizer.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
#include "BuildingManager.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include <string>

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

      switch (id)
        {
        case PlanktonField:
          if (ressources.getCurrentQuantity (RessourceType::Food) >= 5)
            {
              achievements.unlock (id);
            }
          break;

        case FirstSandNest:
          if (ressources.getCurrentQuantity (RessourceType::Sand) >= 1)
            {
              achievements.unlock (id);
            }
          break;

        default:
          break;
        }
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
          && ressources.getNetProduction (RessourceType::Food) >= 1)
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
