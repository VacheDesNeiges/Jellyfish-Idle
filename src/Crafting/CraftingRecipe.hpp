#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "GameIDsTypes.hpp"
#include "SaveAndLoadable.hpp"

struct RecipeSaveData
{
    unsigned lvl;
    double currentProgress;
    double progressNeeded;
    bool craftOngoing;
    bool craftDone;
    bool keepCraftingEnabled;
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
    explicit CraftingRecipe(const nlohmann::json &);
    ~CraftingRecipe() = default;

    unsigned getRecipelvl() const;
    void start();
    void cancel();
    bool tick();
    bool isOngoing() const;
    bool isDone() const;
    bool applyExp();
    void reset();
    bool hasKeepCraftingEnabled() const;
    void setKeepCraftingMode(bool);
    unsigned getRemainingTicks() const;
    unsigned getTotalRequiredTicks() const;
    std::string getName() const;

    std::vector<std::pair<RessourceType, double>> getRecipe() const;
    std::vector<std::pair<RessourceType, double>> getBaseResult() const;

    RecipeSaveData getData() const override;
    void loadData(const RecipeSaveData &) override;

  private:
    RecipeLevel getLevelData() const;

    bool craftOngoing = false;
    bool done = false;
    bool keepCraftingMode = false;
    std::string recipeName;
    RecipeLevel level;

    unsigned baseTicksForCraft;
    unsigned remainingTicksToCraft;

    std::vector<std::pair<RessourceType, double>> recipe;
    std::vector<std::pair<RessourceType, double>> baseResult;
};
