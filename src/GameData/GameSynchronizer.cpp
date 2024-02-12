#include "GameSynchronizer.hpp"

#include "Building.hpp"
#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "MultiplierDataView.hpp"

#include <iostream>
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

  convertRessources ();

  // Ressource production
  systems->ressources->produce (
      addMaps (systems->buildings->getProductionRates (),
               systems->jellies->getProductionRates ()));

  if (systems->crafts->tick ())
    {
      for (const auto &[ressource, prod] : systems->crafts->getCraftResults ())
        {
          std::cout << "id : " << static_cast<int> (ressource)
                    << "prod : " << prod << "\n";
          systems->ressources->add (ressource, prod);
          std::cout << "stone slabs : "
                    << systems->ressources->getCurrentQuantity (
                           RessourceType::StoneSlab)
                    << "\n";
        }
    }

  systems->depth->ExploreDepth (
      systems->jellies->getNum (JellyJobs::ExploreTheDepths));

  // Jobs experience, with bool value return to update multipliers
  distributeExp ();

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
GameSynchronizer::synchronizeSystems () const
{
  systems->crafts->updateAssignments ();
  systems->multipliers->recomputeMultipliers ();
  gameTick ();
}

void
GameSynchronizer::distributeExp () const
{
  bool hasLeveledUp = systems->jellies->distributeJobExp ();

  if (systems->crafts->distributeCraftsExp ())
    hasLeveledUp = true;

  if (hasLeveledUp)
    systems->multipliers->recomputeMultipliers ();
}

void
GameSynchronizer::convertRessources () const
{
  for (const auto building : Building::convertionBuildings)
    {
      const auto &prod = systems->buildings->getProduction (building);
      const auto &cons = systems->buildings->getConsumption (building);
      systems->ressources->tryConvert (cons, prod);
    }
}