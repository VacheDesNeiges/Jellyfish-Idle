#include "InputHandler.hpp"
#include "GameIDsTypes.hpp"
#include "GameSystems.hpp"
#include <memory>
#include <unordered_map>

InputHandler::InputHandler (std::shared_ptr<SystemPtrs> sy)

    : systems (sy)
{
}

void
InputHandler::useAbility (AbilityType t) const
{
  if (systems->abilities->isUsable (t))
    {
      systems->ressources->substract (systems->abilities->getAbilityCost (t));
      systems->ressources->add (systems->abilities->getProduction (t));
    }
}

bool
InputHandler::assignJelly (JellyJob j) const
{
  bool ret = systems->jellies->assign (j);

  if (j == JobsAlias::ARTISAN)
    systems->crafts->updateAssignments ();

  return ret;
}

bool
InputHandler::unassignJelly (JellyJob j) const
{

  if (j != JobsAlias::ARTISAN)
    return systems->jellies->unasign (j);

  if (systems->crafts->getAssignedNumOfJellies (RecipesAlias::NONE))
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
  systems->ressources->substract (systems->buildings->nextBuyCost (t));
  systems->buildings->buy (t);

  if (systems->buildings->doesIncreasesMaxJellies (t))
    updateMaxNumJellies ();

  if (systems->buildings->doesIncreasesRessourcesMaxQuantities (t))
    updateMaxRessourcesQuantities ();
}

void
InputHandler::buy (UpgradeID id) const
{
  systems->ressources->substract (systems->upgrades->getCost (id));
  systems->upgrades->buy (id);
}

void
InputHandler::updateMaxNumJellies () const
{
  unsigned n = 0;
  for (const auto &b : systems->buildings->getBuildingTypes ())
    {
      n += systems->buildings->getIncreaseToMaxJfish (b);
    }
  systems->jellies->setBonusMaxJellies (n);
}

void
InputHandler::updateMaxRessourcesQuantities () const
{
  std::unordered_map<RessourceType, double> newQuantities;
  for (const auto &b : systems->buildings->getBuildingTypes ())
    {
      for (const auto &[rType, quant] :
           systems->buildings->getIncreasedStorage (b))
        {
          newQuantities[rType] += quant;
        }
    }
  systems->ressources->updateMaxRessourcesQuantities (newQuantities);
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
      systems->ressources->substract (systems->garden->getConsumption (id));
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

void
InputHandler::setKeepCraftingMode (RecipeID id, bool b) const
{
  systems->crafts->setKeepCraftingMode (id, b);
}