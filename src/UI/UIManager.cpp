#include "UIManager.hpp"
#include "AchievementIDs.hpp"
#include "GameSystems.hpp"
#include "imgui.h"

#include <fmt/core.h>
#include <memory>

void
UIManager::bindGameData (std::shared_ptr<GameDataView> viewPtr,
                         std::shared_ptr<InputHandler> inputPtr)
{
  gData = viewPtr;
  inputHandler = inputPtr;
  ressourcesPanel.bindGameData (viewPtr, inputPtr);
  buildingsPanel.bindGameData (viewPtr, inputPtr);
  jobsPanel.bindGameData (viewPtr, inputPtr);
  abilitiesPanel.bindGameData (viewPtr, inputPtr);
  ressourcesPanel.bindGameData (viewPtr, inputPtr);
  depthPanel.bindGameData (viewPtr, inputPtr);
  octopusPanel.bindGameData (viewPtr, inputPtr);
  gardenPanel.bindGameData (viewPtr, inputPtr);
  notifications.bindGameData (viewPtr, inputPtr);
}

void
UIManager::renderUI () const
{
  using enum AchievementIDs;
  ImGui::DockSpaceOverViewport (0, ImGui::GetMainViewport ());

  buildingsPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (FirstJelly))
    jobsPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (LightningAbilityBuyable))
    abilitiesPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (ResearchTabUnlocked))
    researchPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (DepthSystem))
    depthPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (AncientOctopus))
    octopusPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (GardenSystem))
    gardenPanel.render ();

  ressourcesPanel.render ();
  notifications.render ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}
