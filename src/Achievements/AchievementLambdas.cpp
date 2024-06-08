#include "AchievementIDs.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"

#include <cassert>
#include <iostream>

void
AchievementSystem::initLambdas ()
{
  using enum AchievementIDs;
  achievementConditions = {

    // Buildings Achievements
    // -------------------------------------------------------------------

    { BuildingAquaticField,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Sand)
               >= 2;
      } },

    { BuildingSandNest,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Sand)
               >= 5;
      } },

    { BuildingMines,
      [this] () { return depthView ()->getCurrentDepth () >= 20; } },

    // Garden achievements
    // ------------------------------------------------------------------

    { GardenSystem,
      [this] () {
        return buildingsView ()->getBuildingQuantity (
                   BuildingType::AquaticField)
               >= 1;
      } },

    { CulturePlankton, [] () { return true; } },

    { CultureOyster,
      [this] () { return depthView ()->getCurrentDepth () >= 15; } },

    // Ressources Achievements
    // -------------------------------------------------------------------

    { RessourceFood,
      [this] () {
        return ressourcesView ()->getRessourceMaxQuantity (RessourceType::Food)
               > 0;
      } },

    { RessourceGlass,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Glass)
               > 0;
      } },

    { RessourceStoneSlab,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (
                   RessourceType::StoneSlab)
               > 0;
      } },

    { RessourceGlassPane,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (
                   RessourceType::GlassPane)
               > 0;
      } },

    { FirstJelly,
      [this] () { return jelliesView ()->getNumJellies () >= 1; } },

    // Jobs Achievements
    // -------------------------------------------------------------------

    { JobSystem, [this] () { return jelliesView ()->getNumJellies () > 0; } },

    { JobExploreTheDepths,
      [this] () { return jelliesView ()->getNumJellies () >= 2; } },

    { JobMining,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::Telekinesis);
      } },

    { JobArtisan,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::AdvancedTelekinesis);
      } },

    { FocusingUpgradeBought,
      [this] () { return upgradeView ()->isBought (UpgradeID::Focusing); } },

    { TelekinesisUpgradeBought,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::Telekinesis);
      } },

    { AdvancedTelekinesisUpgradeBought,
      [this] () {
        return upgradeView ()->isBought (UpgradeID::AdvancedTelekinesis);
      } },

    { LightningAbilityBuyable,
      [this] () {
        return ressourcesView ()->getRessourceQuantity (RessourceType::Insight)
               >= 1;
      } },

    { ResearchTabUnlocked, [] () { return false; } },

    { AncientOctopus,
      [this] () { return depthView ()->getCurrentDepth () >= 10; } },

  };

  for (const auto &id : allAchievementsIDs)
    {
      assert (achievementConditions.contains (id)
              || std::cerr << "Missing achievement enum val : "
                           << static_cast<int> (id) << "\n");
    }
}