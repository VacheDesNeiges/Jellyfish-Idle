#include "GameSynchronizer.hpp"

#include "GameDataView.hpp"
#include "GameIDsTypes.hpp"
#include "GameSystems.hpp"

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
  for (const auto recipe : systems->crafts->getRecipeTypes ())
    {
      if (!systems->crafts->craftIsOngoing (recipe)
          && systems->crafts->isKeepCraftingEnabled (recipe)
          && systems->crafts->canAfford (recipe))
        {
          for (const auto &[rType, quant] :
               systems->crafts->getRecipe (recipe))
            {
              systems->ressources->add (
                  rType,
                  -quant * systems->crafts->getAssignedNumOfJellies (recipe));
            }
          systems->crafts->startRecipe (recipe);
        }
    }

  systems->depth->ExploreDepth (systems->jellies->getNum (JobsAlias::EXPLORE));

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
  systems->ressources->recomputeMaxQuantities ();
  gameTick ();
}

void
GameSynchronizer::distributeExp () const
{
  if (systems->achievements->isUnlocked (UpgradesAlias::LEVELING))
    {

      systems->jellies->distributeJobExp ();

      systems->crafts->distributeCraftsExp ();
    }
}

void
GameSynchronizer::convertRessources () const
{
  for (const auto building : systems->buildings->getConversionBuildingTypes ())
    {
      const auto &prod = systems->buildings->getProduction (building);
      const auto &cons = systems->buildings->getConsumption (building);
      systems->ressources->tryConvert (cons, prod);
    }

  for (const auto culture : systems->garden->getCultureTypes ())
    {
      if (systems->garden->isOngoing (culture))
        {
          const auto &prod = systems->garden->getProduction (culture);

          const auto &cons = systems->garden->getConsumption (culture);
          systems->ressources->tryConvert (cons, prod);
        }
    }
}