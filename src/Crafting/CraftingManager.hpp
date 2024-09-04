#pragma once
#include "CraftingRecipe.hpp"
#include "GameDataAccess.hpp"
#include "GameIDsTypes.hpp"
#include "SaveAndLoadable.hpp"

#include <unordered_map>
#include <utility>

class CraftingManager final
    : public GameDataAccess,
      public SaveAndLoadable<std::vector<std::pair<RecipeID, RecipeSaveData>>>
{
  public:
    CraftingManager();
    ~CraftingManager() = default;
    CraftingManager(const CraftingManager &) = delete;
    CraftingManager(CraftingManager &&) = delete;
    CraftingManager &operator=(const CraftingManager &) = delete;
    CraftingManager &operator=(CraftingManager &&) = delete;

    bool assign(RecipeID);
    bool unasign(RecipeID);
    bool canAfford(RecipeID) const;

    void setKeepCraftingMode(RecipeID, bool);
    bool isKeepCraftingEnabled(RecipeID) const;

    bool craftIsOngoing(RecipeID) const;
    bool distributeCraftsExp();
    void startRecipe(RecipeID);
    void cancelRecipe(RecipeID);

    unsigned getRemainingTicks(RecipeID) const;
    unsigned getTotalRequiredTicks(RecipeID) const;
    unsigned getAssignedNumOfJellies(RecipeID) const;
    unsigned getAssignedNumOfJelliesOnOngoingCrafts() const;
    void updateAssignments();
    std::string getName(RecipeID) const;

    bool tick();
    std::vector<std::pair<RessourceType, double>> getRecipe(RecipeID) const;
    std::vector<std::pair<RessourceType, double>> getCraftResults();
    std::vector<std::pair<RessourceType, double>> getCraftResult(
        RecipeID) const;

    std::span<const RecipeID> getRecipeTypes() const;

    std::vector<std::pair<RecipeID, RecipeSaveData>> getData() const override;
    void loadData(
        const std::vector<std::pair<RecipeID, RecipeSaveData>> &) override;

  private:
    unsigned assignedJelliesToCrafting = 0;
    std::unordered_map<RecipeID, unsigned> assignedJelliesToRecipes;
    std::unordered_map<RecipeID, CraftingRecipe> recipes;
    std::vector<RecipeID> recipeTypes;
};
