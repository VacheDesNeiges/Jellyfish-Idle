#include "InputHandler.hpp"
#include "GameSystems.hpp"
#include "Jellyfish.hpp"
#include "RecipeID.hpp"
#include "UpgradeId.hpp"
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

  if (j != JellyJobs::Artisan)
    return systems->jellies->unasign (j);

  if (systems->crafts->getAssignedNumOfJellies (RecipeID::NoneRecipe))
    {
      systems->jellies->unasign (j);
      systems->crafts->updateAssignments ();
      return true;
    }
  return false;
}

void
InputHandler::gatherSand () const
{
  systems->ressources->gatherSand ();
}

void
InputHandler::lureJellyfish () const
{
  const auto &[rType, quant] = systems->jellies->getLureCost ();
  systems->ressources->add (rType, -quant);
  systems->jellies->createJellyfish ();
}

void
InputHandler::buy (BuildingType t) const
{
  for (const auto &[rType, quant] : systems->buildings->nextBuyCost (t))
    {
      systems->ressources->add (rType, -quant);
    }
  systems->buildings->buy (t);
  systems->multipliers->buildingBoughtUpdate (t);

  if (systems->buildings->doesIncreasesMaxJellies (t))
    updateMaxNumJellies ();
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

void
InputHandler::startCulture (AquaCultureID id) const
{
  if (systems->garden->canAffordTick (id))
    {
      // TODO : Add a function that takes a vector and does the following loop
      // internaly
      for (const auto &[rType, quant] : systems->garden->getConsumption (id))
        {
          systems->ressources->add (rType, -quant);
        }
      systems->garden->startCulture (id);
    }
}

void
InputHandler::cancelCulture (AquaCultureID id) const
{
  if (systems->garden->isOngoing (id))
    {
      systems->garden->cancelCulture (id);
    }
}

void
InputHandler::unassignToField (AquaCultureID id) const
{
  systems->garden->unnasign (id);
}

void
InputHandler::assignToField (AquaCultureID id) const
{
  systems->garden->assign (id);
}

void
InputHandler::removeCurrentNotification () const
{
  systems->achievements->popNotification ();
}