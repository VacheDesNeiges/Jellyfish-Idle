#pragma once
#include "GameIDsTypes.hpp"
#include "GameSystems.hpp"
#include <memory>

enum class RecipeID;

class InputHandler
{
public:
  explicit InputHandler (std::shared_ptr<SystemPtrs>);

  void gatherSand () const;
  void lureJellyfish () const;
  void buy (BuildingType) const;
  void buy (UpgradeID) const;

  bool unassignJelly (JellyJob) const;
  bool assignJelly (JellyJob) const;

  void useAbility (AbilityType) const;

  void startRecipe (RecipeID) const;
  void cancelRecipe (RecipeID) const;
  void assignToRecipe (RecipeID) const;
  void unassignToRecipe (RecipeID) const;

  void startCulture (AquaCultureID) const;
  void cancelCulture (AquaCultureID) const;
  void unassignToField (AquaCultureID) const;
  void assignToField (AquaCultureID) const;

  void removeCurrentNotification () const;

private:
  std::shared_ptr<SystemPtrs> systems;

  void updateMaxNumJellies () const;
};