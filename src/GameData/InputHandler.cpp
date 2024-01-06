#include "InputHandler.hpp"
#include "JellyfishManager.hpp"
#include "RessourceManager.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include <memory>

InputHandler::InputHandler (std::shared_ptr<RessourceManager> r,
                            std::shared_ptr<BuildingManager> b,
                            std::shared_ptr<JellyfishManager> j,
                            std::shared_ptr<AbilityManager> abi,
                            std::shared_ptr<UpgradeManager> u)

    : ressources (r), buildings (b), jellies (j), abilities (abi), upgrades (u)
{
}

void
InputHandler::useAbility (AbilityType t)
{
  if (abilities->isUsable (t))
    {
      for (const auto &[rType, quant] : abilities->getAbilityCost (t))
        {
          ressources->add (rType, -quant);
        }

      for (const auto &[rType, quant] : abilities->getProduction (t))
        {
          ressources->add (rType, quant);
        }
    }
}

bool
InputHandler::assignJelly (JellyJobs j)
{
  return jellies->assign (j);
}

bool
InputHandler::unassignJelly (JellyJobs j)
{
  return jellies->unasign (j);
}

void
InputHandler::gatherFood ()
{
  ressources->gatherFood ();
}

void
InputHandler::buy (BuildingType t)
{
  for (const auto &[rType, quant] : buildings->nextBuyCost (t))
    {
      ressources->add (rType, -quant);
    }
  buildings->buy (t);

  if (buildings->doesIncreasesMaxJellies (t))
    updateMaxNumJellies ();
}

void
InputHandler::buy (UpgradeID id)
{
  for (const auto &[rType, quant] : upgrades->getCost (id))
    {
      ressources->add (rType, -quant);
    }
  upgrades->buy (id);
}

void
InputHandler::updateMaxNumJellies ()
{
  using enum BuildingType;
  unsigned n = 0;
  for (const auto &b : Building::BuildingTypes)
    {
      n += buildings->getIncreaseToMaxJfish (b);
    }
  jellies->setBonusMaxJellies (n);
}
