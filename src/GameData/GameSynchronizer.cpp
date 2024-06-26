#include "GameSynchronizer.hpp"

#include "Building.hpp"
#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "UpgradeId.hpp"

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
  convertRessources ();

  // Ressource production
  systems->ressources->produce (
      addMaps (systems->buildings->getProductionRates (),
               systems->jellies->getProductionRates ()));

  if (systems->crafts->tick ())
    {
      for (const auto &[ressource, prod] : systems->crafts->getCraftResults ())
        {
          systems->ressources->add (ressource, prod);
        }
    }

  systems->depth->ExploreDepth (
      systems->jellies->getNum (JellyJobs::ExploreTheDepths));

  // Jobs experience, with bool value return to update multipliers
  distributeExp ();

  checkAchievements ();
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
  if (systems->achievements->isUnlocked (UpgradeID::Leveling))
    {

      bool hasLeveledUp = systems->jellies->distributeJobExp ();

      if (systems->crafts->distributeCraftsExp ())
        hasLeveledUp = true;

      if (hasLeveledUp)
        systems->multipliers->recomputeMultipliers ();
    }
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

  for (const auto culture : AquaCulture::CultureTypes)
    {
      if (systems->garden->isOngoing (culture))
        {
          const auto &prod = systems->garden->getProduction (culture);

          const auto &cons = systems->garden->getConsumption (culture);
          systems->ressources->tryConvert (cons, prod);
        }
    }
}