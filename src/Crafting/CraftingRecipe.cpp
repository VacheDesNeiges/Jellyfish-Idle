#include "CraftingRecipe.hpp"
#include "GameIDsTypes.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

CraftingRecipe::CraftingRecipe(const nlohmann::json &recipeData)
{
    try
    {
        recipeName = recipeData.at("Name");
        baseTicksForCraft = recipeData.at("BaseTicksRequired");
        remainingTicksToCraft = baseTicksForCraft;
        level = {1, 0, 100};

        for (const auto &cost : recipeData.at("Cost"))
        {
            recipe.emplace_back(RessourceType(cost.at("RessourceID")),
                                cost.at("Quantity"));
        }

        for (const auto &production : recipeData.at("Result"))
        {
            baseResult.emplace_back(RessourceType(production.at("RessourceID")),
                                    production.at("Quantity"));
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "Error while parsing a recipe :\n" << e.what() << "\n";
        abort();
    }
}

void CraftingRecipe::start()
{
    craftOngoing = true;
    remainingTicksToCraft = baseTicksForCraft;
}

void CraftingRecipe::cancel()
{
    craftOngoing = false;
    remainingTicksToCraft = baseTicksForCraft;
}

unsigned CraftingRecipe::getRemainingTicks() const
{
    return remainingTicksToCraft;
}

std::vector<std::pair<RessourceType, double>> CraftingRecipe::getRecipe() const
{
    return recipe;
}

std::vector<std::pair<RessourceType, double>> CraftingRecipe::getBaseResult()
    const
{
    return baseResult;
}

bool CraftingRecipe::tick()
{
    if (craftOngoing)
    {
        remainingTicksToCraft--;
        if (remainingTicksToCraft == 0)
        {
            craftOngoing = false;
            done = true;
            level.currentProgress += 10;
        }
    }
    return done;
}

bool CraftingRecipe::isDone() const
{
    return done;
}

unsigned CraftingRecipe::getTotalRequiredTicks() const
{
    return baseTicksForCraft;
}

std::string CraftingRecipe::getName() const
{
    return recipeName;
}

bool CraftingRecipe::isOngoing() const
{
    return craftOngoing;
}

void CraftingRecipe::reset()
{
    done = false;
    craftOngoing = false;
    remainingTicksToCraft = baseTicksForCraft;
}

unsigned CraftingRecipe::getRecipelvl() const
{
    return level.lvl;
}

bool CraftingRecipe::applyExp()
{
    bool hasLeveledUp = false;
    while (level.currentProgress >= level.progressNeeded)
    {
        hasLeveledUp = true;
        level.lvl += 1;
        level.currentProgress -= level.progressNeeded;
        level.progressNeeded =
            10 * level.lvl * (level.lvl / std::log(level.lvl));
    }
    return hasLeveledUp;
}

RecipeLevel CraftingRecipe::getLevelData() const
{
    return level;
}

RecipeSaveData CraftingRecipe::getData() const
{
    RecipeSaveData result = {};
    result.craftDone = done;
    result.craftOngoing = craftOngoing;
    result.keepCraftingEnabled = keepCraftingMode;
    result.remainingTicksToCraft = remainingTicksToCraft;
    result.lvl = level.lvl;
    result.currentProgress = level.currentProgress;
    result.progressNeeded = level.progressNeeded;

    return result;
}

void CraftingRecipe::loadData(const RecipeSaveData &data)
{
    done = data.craftDone;
    craftOngoing = data.craftOngoing;
    remainingTicksToCraft = data.remainingTicksToCraft;
    level.lvl = data.lvl;
    level.currentProgress = data.currentProgress;
    level.progressNeeded = data.progressNeeded;
    keepCraftingMode = data.keepCraftingEnabled;
}

bool CraftingRecipe::hasKeepCraftingEnabled() const
{
    return keepCraftingMode;
}

void CraftingRecipe::setKeepCraftingMode(bool newMode)
{
    keepCraftingMode = newMode;
}
