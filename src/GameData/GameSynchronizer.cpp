#include "GameSynchronizer.hpp"
#include "AbilityManager.hpp"
#include "AchievementSystem.hpp"
#include "BuildingManager.hpp"
#include "DepthSystem.hpp"
#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "JellyfishManager.hpp"
#include "MultiplierDataView.hpp"
#include "MultipliersRegister.hpp"
#include "RessourceManager.hpp"
#include "UpgradeManager.hpp"
#include <memory>

GameSynchronizer::GameSynchronizer (std::shared_ptr<SystemPtrs> ptrs)
    : systems (ptrs)
{
}

void
GameSynchronizer::gameTick () const
{
  systems->ressources->zerosValuePerTick ();
  // Ressource consumption
  systems->ressources->consume (systems->jellies->getConsumptionRates ());
  // Ressource conversion here
  // Ressource production
  systems->ressources->produce (
      addMaps (systems->buildings->getProductionRates (),
               systems->jellies->getProductionRates ()));

  systems->depth->ExploreDepth (
      systems->jellies->getNum (JellyJobs::ExploreTheDepths));

  // Jobs experience, with bool value return to update multipliers

  checkAchievements ();
  checkJellyfishArrival ();
}

void
GameSynchronizer::checkJellyfishArrival () const
{
  static short gameTicksInterval = 0;
  if (systems->jellies->getNumJellies ()
      == systems->jellies->getMaxNumJellies ())
    {
      gameTicksInterval = 0;
    }
  else
    {
      gameTicksInterval++;
      if (gameTicksInterval == 8
          && systems->ressources->getNetProduction (RessourceType::Food)
                 >= systems->jellies->getFoodRequiredPerJellyfishPerSec () / 2)
        {
          gameTicksInterval = 0;
          systems->jellies->createJellyfish ();
        }
      if (gameTicksInterval >= 8)
        gameTicksInterval = 0;
    }
}

void
GameSynchronizer::checkAchievements () const
{
  systems->achievements->checkAchievements ();
}

std::unordered_map<RessourceType, double>
GameSynchronizer::addMaps (
    const std::unordered_map<RessourceType, double> &map1,
    const std::unordered_map<RessourceType, double> &map2) const
{
  auto result = map1;

  for (const auto &[key, value] : map2)
    {
      result[key] += value;
    }
  return result;
}

void
GameSynchronizer::update () const
{
  systems->multipliers->recomputeMultipliers ();
  gameTick ();
}
