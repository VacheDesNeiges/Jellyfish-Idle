#include "UIManager.hpp"
#include "AchievementDataView.hpp"
#include "AchievementSystem.hpp"
#include "Building.hpp"
#include "DepthDataView.hpp"
#include "GameDataView.hpp"
#include "GameSystems.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <fmt/core.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

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
}

void
UIManager::renderUI () const
{
  ImGui::DockSpaceOverViewport (ImGui::GetMainViewport ());

  ImGui::Begin ("Tab", nullptr, ImGuiDockNodeFlags_NoTabBar);
  if (ImGui::BeginTabBar ("Fish", ImGuiTabBarFlags_None))
    {
      buildingsPanel.render ();

      if (gData->getAchievementsView ()->isUnlocked (
              AchievementIDs::FirstJelly))
        jobsPanel.render ();

      if (gData->getAchievementsView ()->isUnlocked (
              AchievementIDs::FirstInsightAbility))
        abilitiesPanel.render ();

      if (gData->getAchievementsView ()->isUnlocked (
              AchievementIDs::ResearchTabUnlocked))
        researchPanel.render ();

      if (gData->getAchievementsView ()->isUnlocked (
              AchievementIDs::JobExploreTheDepths)
          && ImGui::BeginTabItem ("Depths"))
        {
          std::string depthString
              = fmt::format ("Current Depth : {} meters",
                             gData->getDepthView ()->getCurrentDepth ());
          ImGui::Text ("%s", depthString.c_str ());
          ImGui::ProgressBar (
              gData->getDepthView ()->getCurrentProgress ()
              / gData->getDepthView ()->getProgressNeededForNextIncrease ());
          ImGui::EndTabItem ();
        }

      ImGui::EndTabBar ();
    }

  ImGui::End ();

  ressourcesPanel.render ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}
