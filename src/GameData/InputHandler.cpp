#include "InputHandler.hpp"
#include "GameIDsTypes.hpp"
#include "GameSystems.hpp"
#include <memory>
#include <unordered_map>

InputHandler::InputHandler(std::shared_ptr<SystemPtrs> sy)

    : systems(sy)
{
}

void InputHandler::useAbility(AbilityType abiType) const
{
    if (systems->abilities->isUsable(abiType))
    {
        systems->ressources->substract(
            systems->abilities->getAbilityCost(abiType));
        systems->ressources->add(systems->abilities->getProduction(abiType));
    }
}

bool InputHandler::assignJelly(JellyJob jJob) const
{
    bool ret = systems->jellies->assign(jJob);

    if (jJob == JobsAlias::ARTISAN)
        systems->crafts->updateAssignments();

    return ret;
}

bool InputHandler::unassignJelly(JellyJob jJob) const
{

    if (jJob != JobsAlias::ARTISAN)
        return systems->jellies->unasign(jJob);

    if (systems->crafts->getAssignedNumOfJellies(RecipesAlias::NONE) > 0)
    {
        systems->jellies->unasign(jJob);
        systems->crafts->updateAssignments();
        return true;
    }
    return false;
}

void InputHandler::gatherSand() const
{
    systems->ressources->gatherSand();
}

void InputHandler::lureJellyfish() const
{
    const auto &[rType, quant] = systems->jellies->getLureCost();
    systems->ressources->add(rType, -quant);
    systems->jellies->createJellyfish();
}

void InputHandler::buy(BuildingType bType) const
{
    systems->ressources->substract(systems->buildings->nextBuyCost(bType));
    systems->buildings->buy(bType);

    if (systems->buildings->doesIncreasesMaxJellies(bType))
        updateMaxNumJellies();

    if (systems->buildings->doesIncreasesRessourcesMaxQuantities(bType))
        updateMaxRessourcesQuantities();
}

void InputHandler::buy(UpgradeID id) const
{
    systems->ressources->substract(systems->upgrades->getCost(id));
    systems->upgrades->buy(id);
}

void InputHandler::updateMaxNumJellies() const
{
    unsigned updatedNum = 0;
    for (const auto &bType : systems->buildings->getBuildingTypes())
    {
        updatedNum += systems->buildings->getIncreaseToMaxJfish(bType);
    }
    systems->jellies->setBonusMaxJellies(updatedNum);
}

void InputHandler::updateMaxRessourcesQuantities() const
{
    std::unordered_map<RessourceType, double> newQuantities;
    for (const auto &bType : systems->buildings->getBuildingTypes())
    {
        for (const auto &[rType, quant] :
             systems->buildings->getIncreasedStorage(bType))
        {
            newQuantities[rType] += quant;
        }
    }
    systems->ressources->updateMaxRessourcesQuantities(newQuantities);
}

void InputHandler::startRecipe(RecipeID id) const
{
    if (systems->crafts->canAfford(id))
    {
        for (const auto &[rType, quant] : systems->crafts->getRecipe(id))
        {
            systems->ressources->add(
                rType, -quant * systems->crafts->getAssignedNumOfJellies(id));
        }
        systems->crafts->startRecipe(id);
    }
}

void InputHandler::cancelRecipe(RecipeID id) const
{
    systems->crafts->cancelRecipe(id);
}

void InputHandler::assignToRecipe(RecipeID id) const
{
    systems->crafts->assign(id);
}

void InputHandler::unassignToRecipe(RecipeID id) const
{
    systems->crafts->unasign(id);
}

void InputHandler::startCulture(AquaCultureID id) const
{
    if (systems->garden->canAffordTick(id))
    {
        systems->ressources->substract(systems->garden->getConsumption(id));
        systems->garden->startCulture(id);
    }
}

void InputHandler::cancelCulture(AquaCultureID id) const
{
    if (systems->garden->isOngoing(id))
    {
        systems->garden->cancelCulture(id);
    }
}

void InputHandler::unassignToField(AquaCultureID id) const
{
    systems->garden->unnasign(id);
}

void InputHandler::assignToField(AquaCultureID id) const
{
    systems->garden->assign(id);
}

void InputHandler::removeCurrentNotification() const
{
    systems->achievements->popNotification();
}

void InputHandler::setKeepCraftingMode(RecipeID id, bool b) const
{
    systems->crafts->setKeepCraftingMode(id, b);
}

bool InputHandler::completeQuest(QuestLineEnum ql) const
{
    if (const auto &cost = systems->quests->getCurrentQuestRequirements(ql);
        systems->ressources->canAfford(cost))
    {
        systems->ressources->substract(cost);
        systems->quests->completeQuest(ql);
        return true;
    }
    return false;
}
