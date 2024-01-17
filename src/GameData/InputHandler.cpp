#include "InputHandler.hpp"
#include "AbilityManager.hpp"
#include "BuildingManager.hpp"
#include "GameSystems.hpp"
#include "JellyfishManager.hpp"
#include "MultipliersRegister.hpp"
#include "RessourceManager.hpp"
#include "UpgradeId.hpp"
#include "UpgradeManager.hpp"
#include <memory>

InputHandler::InputHandler (std::shared_ptr<SystemPtrs> sy)

    : systems (sy)
{
}

void
InputHandler::useAbility (AbilityType t) const
{
  if (systems->abilities->isUsable (t))
    {
      for (const auto &[rType, quant] : systems->abilities->getAbilityCost (t))
        {
          systems->ressources->add (rType, -quant);
        }

      for (const auto &[rType, quant] : systems->abilities->getProduction (t))
        {
          systems->ressources->add (rType, quant);
        }
    }
}

bool
InputHandler::assignJelly (JellyJobs j) const
{
  return systems->jellies->assign (j);
}

bool
InputHandler::unassignJelly (JellyJobs j) const
{
  return systems->jellies->unasign (j);
}

void
InputHandler::gatherFood () const
{
  systems->ressources->gatherFood ();
}

void
InputHandler::buy (BuildingType t) const
{
  for (const auto &[rType, quant] : systems->buildings->nextBuyCost (t))
    {
      systems->ressources->add (rType, -quant);
    }
  systems->buildings->buy (t);

  if (systems->buildings->doesIncreasesMaxJellies (t))
    updateMaxNumJellies ();

  systems->multipliers->buildingBought (t);
}

void
InputHandler::buy (UpgradeID id) const
{
  for (const auto &[rType, quant] : systems->upgrades->getCost (id))
    {
      systems->ressources->add (rType, -quant);
    }
  systems->upgrades->buy (id);
}

void
InputHandler::updateMaxNumJellies () const
{
  using enum BuildingType;
  unsigned n = 0;
  for (const auto &b : Building::BuildingTypes)
    {
      n += systems->buildings->getIncreaseToMaxJfish (b);
    }
  systems->jellies->setBonusMaxJellies (n);
}
