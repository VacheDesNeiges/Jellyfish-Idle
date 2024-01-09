#include "GameSynchronizer.hpp"
#include "AbilityManager.hpp"
#include "AchievementSystem.hpp"
#include "BuildingManager.hpp"
#include "DepthSystem.hpp"
#include "GameDataView.hpp"
#include "JellyfishManager.hpp"
#include "RessourceManager.hpp"
#include "UpgradeManager.hpp"
#include <memory>

GameSynchronizer::GameSynchronizer (std::shared_ptr<RessourceManager> r,
                                    std::shared_ptr<BuildingManager> b,
                                    std::shared_ptr<JellyfishManager> j,
                                    std::shared_ptr<AchievementSystem> ach,
                                    std::shared_ptr<AbilityManager> abi,
                                    std::shared_ptr<DepthSystem> d,
                                    std::shared_ptr<UpgradeManager> u)

    : ressources (r), buildings (b), jellies (j), achievements (ach),
      abilities (abi), depth (d), upgrades (u)
{
}

void
GameSynchronizer::gameTick () const
{
  ressources->zerosValuePerTick ();
  // Ressource consumption
  ressources->consume (jellies->getConsumptionRates ());
  // Ressource conversion here
  // Ressource production
  ressources->produce (addMaps (buildings->getProductionRates (),
                                jellies->getProductionRates ()));

  depth->ExploreDepth (jellies->getNum (JellyJobs::ExploreTheDepths));

  checkAchievements ();
  checkJellyfishArrival ();
}

void
GameSynchronizer::checkJellyfishArrival () const
{
  static short gameTicksInterval = 0;
  if (jellies->getNumJellies () == jellies->getMaxNumJellies ())
    {
      gameTicksInterval = 0;
    }
  else
    {
      gameTicksInterval++;
      if (gameTicksInterval == 8
          && ressources->getNetProduction (RessourceType::Food)
                 >= jellies->getFoodRequiredPerJellyfishPerSec () / 2)
        {
          gameTicksInterval = 0;
          jellies->createJellyfish ();
        }
      if (gameTicksInterval >= 8)
        gameTicksInterval = 0;
    }
}

void
GameSynchronizer::checkAchievements () const
{
  achievements->checkAchievements ();
}

std::map<RessourceType, double>
GameSynchronizer::addMaps (const std::map<RessourceType, double> &map1,
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
GameSynchronizer::update () const
{
  gameTick ();
}
