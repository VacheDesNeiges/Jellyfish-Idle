#pragma once
#include "GameSystems.hpp"
#include <memory>

enum class BuildingType;
enum class JellyJobs;
enum class AbilityType;
enum class UpgradeID;
enum class RecipeID;

class InputHandler
{
public:
  explicit InputHandler (std::shared_ptr<SystemPtrs>);

  void gatherFood () const;
  void buy (BuildingType) const;
  void buy (UpgradeID) const;

  bool unassignJelly (JellyJobs) const;
  bool assignJelly (JellyJobs) const;

  void useAbility (AbilityType) const;

  void startRecipe (RecipeID) const;
  void cancelRecipe (RecipeID) const;

private:
  std::shared_ptr<SystemPtrs> systems;

  void updateMaxNumJellies () const;
};