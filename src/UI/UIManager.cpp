#include "UIManager.hpp"
#include "Achievement.hpp"
#include "Building.hpp"
#include "GameDataSynchronizer.hpp"
#include "InsightAbility.hpp"
#include "Jellyfish.hpp"
#include "Ressource.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <fmt/core.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

void
UIManager::bindGameData (std::shared_ptr<GameDataSynchronizer> ptr)
{
  gData = ptr;
  ressourcesPanel.bindGameData (ptr);
  buildingsPanel.bindGameData (ptr);
  jobsPanel.bindGameData (ptr);
  abilitiesPanel.bindGameData (ptr);
  ressourcesPanel.bindGameData (ptr);
}

void
UIManager::renderUI () const
{
  ImGui::DockSpaceOverViewport (ImGui::GetMainViewport ());

  ImGui::Begin ("Tab", nullptr, ImGuiDockNodeFlags_NoTabBar);
  if (ImGui::BeginTabBar ("Fish", ImGuiTabBarFlags_None))
    {
      buildingsPanel.render ();

      if (gData->isUnlocked (AchievementIDs::FirstJelly))
        jobsPanel.render ();

      if (gData->isUnlocked (AchievementIDs::FirstInsightAbility))
        abilitiesPanel.render ();

      if (gData->isUnlocked (AchievementIDs::ResearchTabUnlocked))
        researchPanel.render ();

      if (gData->isUnlocked (AchievementIDs::JobExploreTheDepths)
          && ImGui::BeginTabItem ("Depths"))
        {
          std::string depthString = fmt::format ("Current Depth : {} meters",
                                                 gData->getCurrentDepth ());
          ImGui::Text ("%s", depthString.c_str ());
          ImGui::ProgressBar (gData->getDepthProgress ());
          ImGui::EndTabItem ();
        }

      ImGui::EndTabBar ();
    }

  ImGui::End ();

  ressourcesPanel.render ();

  ImGui::ShowDemoWindow ();
  ImGui::ShowStyleEditor ();
}
