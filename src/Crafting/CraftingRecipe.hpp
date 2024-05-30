#pragma once
#include <utility>
#include <vector>

#include "RecipeID.hpp"
#include "Ressource.hpp"
#include "SaveAndLoadable.hpp"

struct RecipeSaveData
{
  unsigned lvl;
  double currentProgress;
  double progressNeeded;
  bool craftOngoing;
  bool craftDone;
  unsigned remainingTicksToCraft;
  unsigned numAssignedWorkers;
};

struct RecipeLevel
{
  unsigned lvl = 0;
  double currentProgress;
  double progressNeeded;
};

class CraftingRecipe : public SaveAndLoadable<RecipeSaveData>
{
public:
  CraftingRecipe () = default;
  explicit CraftingRecipe (RecipeID);
  ~CraftingRecipe () override = default;

  unsigned getRecipelvl () const;
  void start ();
  void cancel ();
  bool tick ();
  bool isOngoing () const;
  bool isDone () const;
  bool applyExp ();
  void reset ();
  unsigned getRemainingTicks () const;
  unsigned getTotalRequiredTicks () const;
  std::string getName () const;

  std::vector<std::pair<RessourceType, double> > getRecipe () const;
  std::vector<std::pair<RessourceType, double> > getBaseResult () const;

  RecipeSaveData getData () const override;
  void loadData (const RecipeSaveData &) override;

  static constexpr std::array<RecipeID, 2> RecipeTypes = {
    RecipeID::StoneSlabRecipe,
    RecipeID::GlassPanelRecipe,
  };

private:
  RecipeLevel getLevelData () const;

  bool craftOngoing = false;
  bool done = false;
  std::string recipeName;
  RecipeLevel level;

  unsigned baseTicksForCraft;
  unsigned remainingTicksToCraft;

  std::vector<std::pair<RessourceType, double> > recipe;
  std::vector<std::pair<RessourceType, double> > baseResult;
};