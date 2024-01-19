#include "InputHandler.hpp"
#include "AbilityManager.hpp"
#include "BuildingManager.hpp"
#include "CraftingRecipe.hpp"
#include "GameSystems.hpp"
#include "Jellyfish.hpp"
#include "JellyfishManager.hpp"
#include "MultipliersRegister.hpp"
#include "RecipeID.hpp"
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
  bool ret = systems->jellies->assign (j);

  if (j == JellyJobs::Artisan)
    systems->crafts->updateAssignments ();

  return ret;
}

bool
InputHandler::unassignJelly (JellyJobs j) const
{
  bool ret = systems->jellies->unasign (j);

  if (j == JellyJobs::Artisan && ret)
    {
      systems->crafts->unasign (RecipeID::NoneRecipe);
      systems->crafts->updateAssignments ();
    }

  return ret;
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

void
InputHandler::startRecipe (RecipeID id) const
{
  if (systems->crafts->canAfford (id))
    {
      for (const auto &[rType, quant] : systems->crafts->getRecipe (id))
        {
          systems->ressources->add (
              rType, -quant * systems->crafts->getAssignedNumOfJellies (id));
        }
      systems->crafts->startRecipe (id);
    }
}

void
InputHandler::cancelRecipe (RecipeID id) const
{
  systems->crafts->cancelRecipe (id);
}

void
InputHandler::assignToRecipe (RecipeID id) const
{
  systems->crafts->assign (id);
}

void
InputHandler::unassignToRecipe (RecipeID id) const
{
  systems->crafts->unasign (id);
}