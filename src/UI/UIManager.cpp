#include "UIManager.hpp"
#include "GameIDsTypes.hpp"
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
  ImGui::DockSpaceOverViewport (0, ImGui::GetMainViewport ());

  buildingsPanel.render ();

  using namespace AchievementsAlias;
  if (gData->getAchievementsView ()->isUnlocked (JOBSYSTEM))
    jobsPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (ABILITYSYSTEM))
    abilitiesPanel.render ();

  researchPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (DEPTHSYSTEM))
    depthPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (OCTOPUS))
    octopusPanel.render ();

  if (gData->getAchievementsView ()->isUnlocked (GARDENSYSTEM))
    gardenPanel.render ();

  ressourcesPanel.render ();
  notifications.render ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}
