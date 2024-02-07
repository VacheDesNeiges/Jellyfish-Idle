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
}

void
UIManager::renderUI () const
{
  ImGui::DockSpaceOverViewport (ImGui::GetMainViewport ());

  buildingsPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (AchievementIDs::FirstJelly))
    jobsPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (
          AchievementIDs::LightningAbilityBuyable))
    abilitiesPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (
          AchievementIDs::ResearchTabUnlocked))
    researchPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (
          AchievementIDs::JobExploreTheDepths))
    depthPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (
          AchievementIDs::AncientOctopus))
    {
      octopusPanel.render ();
    }

  ressourcesPanel.render ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}
